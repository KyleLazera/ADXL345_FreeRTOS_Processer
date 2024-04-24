#include "BME_Data_comp.h"

BME280_S32_t t_fine;

/*
 * @Brief	Derives the compensation values from the read values and stores them in the data structure
 * @Note	This is done by converting pairs of 8 bit values into 16 bit values
 * @Note	The first compensation value for pressure and temp are both unsigned whereas the others are signed
 */
static void Compensation_values_Derivation(BME_Values *values, uint8_t comp_readings[])
{
	uint8_t index;

	//Compensation Values for temperature:
	values->Compensation_Vals.dig_T1 = ((uint16_t)comp_readings[2] << 8) | comp_readings[1];
	values->Compensation_Vals.dig_T2 = ((uint16_t)comp_readings[4] << 8) | comp_readings[3];
	values->Compensation_Vals.dig_T3 = ((uint16_t)comp_readings[6] << 8) | comp_readings[5];

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
 * @Brief	returns value of temperature in DegC
 */
static void BME280_compenstae_temp(BME_Values *values, BME280_S32_t adc_T)
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

void BME_Data_Calculation()
{
	uint8_t bme_new_data[9];
	BME_Values Raw_BME_Data;
	BME280_S32_t temperature;

	Read_Compensation_Values(&Raw_BME_Data);

	while(1)
	{
		comp_count++;
		xQueueReceive(send_raw_i2c, &bme_new_data, _10ms);

		temperature = ((int32_t)bme_new_data[4] << 16) | ((int32_t)bme_new_data[5] << 8) | bme_new_data[6];
		BME280_compenstae_temp(&Raw_BME_Data, temperature);

		xQueueSend(print_i2c_data, &Raw_BME_Data, 0);
	}

}

