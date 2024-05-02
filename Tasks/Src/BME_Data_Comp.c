#include "BME_Data_comp.h"

BME280_S32_t t_fine;

/*
 * @Brief	Derives the compensation values from the read values and stores them in the data structure
 * @Note	This is done by converting pairs of 8 bit values into 16 bit values
 * @Note	The first compensation value for pressure and temp are both unsigned whereas the others are signed
 */
static void Compensation_values_Derivation(BME_Values *values, uint8_t comp_readings[])
{
	//Compensation Values for temperature:
	values->Compensation_Vals.dig_T1 = ((uint16_t)comp_readings[2] << 8) | comp_readings[1];
	values->Compensation_Vals.dig_T2 = ((uint16_t)comp_readings[4] << 8) | comp_readings[3];
	values->Compensation_Vals.dig_T3 = ((uint16_t)comp_readings[6] << 8) | comp_readings[5];

	//Compensation Values for Pressure:
	values->Compensation_Vals.dig_P1 = ((uint16_t)comp_readings[8] << 8) | comp_readings[7];
	values->Compensation_Vals.dig_P2 = ((uint16_t)comp_readings[10] << 8) | comp_readings[9];
	values->Compensation_Vals.dig_P3 = ((uint16_t)comp_readings[12] << 8) | comp_readings[11];
	values->Compensation_Vals.dig_P4 = ((uint16_t)comp_readings[14] << 8) | comp_readings[13];
	values->Compensation_Vals.dig_P5 = ((uint16_t)comp_readings[16] << 8) | comp_readings[15];
	values->Compensation_Vals.dig_P6 = ((uint16_t)comp_readings[18] << 8) | comp_readings[17];
	values->Compensation_Vals.dig_P7 = ((uint16_t)comp_readings[20] << 8) | comp_readings[19];
	values->Compensation_Vals.dig_P8 = ((uint16_t)comp_readings[22] << 8) | comp_readings[21];
	values->Compensation_Vals.dig_P9 = ((uint16_t)comp_readings[24] << 8) | comp_readings[23];


}

/*
 * @Brief	Read compensation values from the device - addresses can be found in data sheet
 * @Note	These values are used for calculation of the data into readable values
 */
static void Read_Compensation_Values(BME_Values *values)
{
	uint8_t starting_address = 0x88;
	uint8_t compensation_values[25];

	I2C_MasterTransmitIT(&BME_Sensor, &starting_address, 0x77, 1);
	while(BME_Sensor.I2C_Bus_Direction != I2C_Ready){}
	I2C_MasterRecieveIT(&BME_Sensor, compensation_values, 0x77, 24);
	while(BME_Sensor.I2C_Bus_Direction != I2C_Ready){}

	Compensation_values_Derivation(values, compensation_values);

}

/*
 * @Brief	Calculates value of temperature in DegC based on raw sensor values
 * @Note	These calculations can be found in the BME280 data sheet
 */
static void BME280_compensate_temp(BME_Values *values, BME280_S32_t adc_T)
{
	BME280_S32_t T;
	float var1, var2;
	uint16_t dig_T1;
	int16_t dig_T2, dig_T3;

	//Initializing values for dig_Tx for easy use
	dig_T1 = values->Compensation_Vals.dig_T1;
	dig_T2 = values->Compensation_Vals.dig_T2;
	dig_T3 = values->Compensation_Vals.dig_T3;

	var1 = (((float)adc_T)/16384.0 - ((float)dig_T1)/1024.0) * ((float)dig_T2);
    var2 = ((((float)adc_T)/131072.0 - ((float)dig_T1)/8192.0) * (((float)adc_T)/131072.0 - ((float)dig_T1)/8192.0)) * ((float)dig_T3);
    t_fine = (BME280_S32_t)(var1 + var2);
    T = (var1 + var2)/5120.0;

    values->temperature = T;
}

/*
 * @Brief	Calculate value of pressure in Pa based on raw sensor values
 * @Note	This formula was collected from the BME280 data-sheet in Appendix A
 * @Note	The data sheet recommends usage of 64-bit calculations for pressure, however, this negatively influences
 * 			the processing time on the stm32f4xx as it is a 32bit processor
 */
static void BME280_compensate_press(BME_Values *values, BME280_S32_t adc_P)
{

	BME280_S32_t var1, var2, var3, var4, var5;
	BME280_S32_t pressure;
	BME280_S32_t pressure_min = 30000;
	BME280_S32_t pressure_max = 110000;

    var1 = (((BME280_S32_t)t_fine) / 2) - (BME280_S32_t)64000;
    var2 = (((var1 / 4) * (var1 / 4)) / 2048) * ((BME280_S32_t)values->Compensation_Vals.dig_P6);
    var2 = var2 + ((var1 * ((BME280_S32_t)values->Compensation_Vals.dig_P5)) * 2);
    var2 = (var2 / 4) + (((BME280_S32_t)values->Compensation_Vals.dig_P4) * 65536);
    var3 = (values->Compensation_Vals.dig_P3 * (((var1 / 4) * (var1 / 4)) / 8192)) / 8;
    var4 = (((BME280_S32_t)values->Compensation_Vals.dig_P2) * var1) / 2;
    var1 = (var3 + var4) / 262144;
    var1 = (((32768 + var1)) * ((BME280_S32_t)values->Compensation_Vals.dig_P1)) / 32768;

    /* Avoid exception caused by division by zero */
    if (var1)
    {
        var5 = (BME280_U32_t)((BME280_U32_t)1048576) - adc_P;
        pressure = ((BME280_U32_t)(var5 - (BME280_U32_t)(var2 / 4096))) * 3125;

        if (pressure < 0x80000000)
        {
            pressure = (pressure << 1) / ((BME280_U32_t)var1);
        }
        else
        {
            pressure = (pressure / (BME280_U32_t)var1) * 2;
        }

        var1 = (((BME280_S32_t)values->Compensation_Vals.dig_P9) * ((BME280_S32_t)(((pressure / 8) * (pressure / 8)) / 8192))) / 4096;
        var2 = (((BME280_S32_t)(pressure / 4)) * ((BME280_S32_t)values->Compensation_Vals.dig_P8)) / 8192;
        pressure = (BME280_U32_t)((BME280_S32_t)pressure + ((var1 + var2 + values->Compensation_Vals.dig_P7) / 16));

        if (pressure < pressure_min)
        {
            pressure = pressure_min;
        }
        else if (pressure > pressure_max)
        {
            pressure = pressure_max;
        }
    }
    else
    {
        pressure = pressure_min;
    }

    values->pressure = pressure;
}

/*
 * @Brief	This function receives the raw I2C value data, and uses compensation values to determine
 * 			the actual temperature.
 */
void BME_Data_Calculation()
{
	uint8_t bme_new_data[9];
	BME_Values Raw_BME_Data;
	BME280_S32_t temperature, pressure;

	//Get compensation values which are hard coded into each sensor and used for the calculations
	Read_Compensation_Values(&Raw_BME_Data);

	while(1)
	{

		comp_count++;
		//Recieve data from the task that reads I2C data
		xQueueReceive(send_raw_i2c, &bme_new_data, portMAX_DELAY);

		//Read the sensor data from the array and format it for either temperature or pressure
		temperature = ((int32_t)bme_new_data[4] << 16) | ((int32_t)bme_new_data[5] << 8) | bme_new_data[6];
		pressure = ((int32_t)bme_new_data[1] << 16) | ((int32_t)bme_new_data[2] << 8) | bme_new_data[3];

		//Pass the raw data into the compensation formulas
		BME280_compensate_temp(&Raw_BME_Data, temperature);
		BME280_compensate_press(&Raw_BME_Data, pressure);

		//Transmit data to the UART gatekeeper task
		xQueueSend(print_i2c_data, &Raw_BME_Data, 0);
	}

}

