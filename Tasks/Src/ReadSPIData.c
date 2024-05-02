#include "ReadSPIData.h"

//uint8_t adxl_data_rec[7];			//Buffer to store the adxl data

/*
 * @Brief	Used to initialize ADXL registers: Set range to +-4g, allow continuous
 * reading of data registers and set transfer frequency at 100Hz.
 */
static void InitADXL()
{
	uint8_t adxl_set_data_format[2] = {0x31, 0x01};
	uint8_t adxl_clear_powerctl_reg[2] = {0x2D, 0x00};
	uint8_t adxl_set_powerctl_reg[2] = {0x2D, 0x08};
	uint8_t adxl_set_bw_rate_reg[2] = {0x2C, 0x0A};

	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_clear_powerctl_reg, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_data_format, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_bw_rate_reg, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_powerctl_reg, 2);
}

void ReadADXLData()
{
	AccelerometerData data;

	uint8_t adxl_address[1] = {0xF2};	//Address of data register to read from
	uint8_t adxl_data_rec[7];			//Buffer to store the adxl data
	int16_t x, y, z;					//Variables that will store the data from the buffer

	InitADXL();

	while(1)
	{
		readingTask++;

		//Reading data from the SPI
		SPI_MultiSlave_RecieveIT(&SPI1_Example, &ADXL, adxl_data_rec, 7, *adxl_address);

		//Take the semaphore - this ensures there is an interrupt enabling the data to be read
		xSemaphoreTake(read_spi, portMAX_DELAY);

		/*
		* Convert the data into usable/readable values - this can be found in the ADXL345 documentation,
		* and send the stored values to a queue.
		*/
		x = ((adxl_data_rec[2] << 8) | adxl_data_rec[1]);
		data.axis = x_axis;
		data.value = x;
		xQueueSend(adxl_data_queue, &data, _5ms);

		y = ((adxl_data_rec[4] << 8) | adxl_data_rec[3]);
		data.axis = y_axis;
		data.value = y;
		xQueueSend(adxl_data_queue, &data, _5ms);

		z = ((adxl_data_rec[6] << 8) | adxl_data_rec[5]);
		data.axis = z_axis;
		data.value = z;
		xQueueSend(adxl_data_queue, &data, _5ms);

	}

}

/*
 * @Brief	Interrupt Service Routine for the SPI Peripheral
 * @Note	Serviced by the SPI_IRQ_Handler function defined in the stm32f4xx_periphDrivers
 */
void SPI1_IRQHandler()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	SPI_IRQ_Handler(&SPI1_Example);

	//Give semaphore to allow SPI data to be read - controls flow by ensuring the interrupt has happened before trying to read the data
	xSemaphoreGiveFromISR(read_spi, &xHigherPriorityTaskWoken);

	//Causes a context switch for the CPU
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


