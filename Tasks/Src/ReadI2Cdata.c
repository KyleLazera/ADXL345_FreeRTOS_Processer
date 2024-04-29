#include "ReadI2CData.h"

const uint8_t slave_address = 0x77;

/*
 * @Brief	Reading data from BME pressure, temperature and humidity Sensor via I2C
 * @Note	This function solely focuses on reading the I2C data, there is not calculations performed to reduce
 * 			the amount of time spent in this task.
 */
void ReadData()
{
	bme_raw_array bme_data_rec;
	uint8_t init_bme[] = {0xF2, 0x01, 0xF4, 0x25, 0xF5, 0x80};
	uint8_t bme_force_measure[] = {0xF4, 0x25, 0xF7};

	//Only transmit the initialization function the first time the thread runs - to initialize the sensor
	if(i2c_count == 0)
	{
		I2C_MasterTransmitIT(&BME_Sensor, init_bme, slave_address, 8);
	}

	i2c_count++;

	I2C_MasterTransmitIT(&BME_Sensor, bme_force_measure, slave_address, 3);
	while(BME_Sensor.I2C_Bus_Direction != I2C_Ready){}
	I2C_MasterRecieveIT(&BME_Sensor, bme_data_rec, slave_address, 8);
	while(BME_Sensor.I2C_Bus_Direction != I2C_Ready){}

	xQueueSend(send_raw_i2c, &bme_data_rec, 0);

}

/*
 * @Brief Interrupt Service Routine for I2C
 */
void I2C1_EV_IRQHandler()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	IRQ_Event_Handler(&BME_Sensor);

	//Causes a context switch for the CPU
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
