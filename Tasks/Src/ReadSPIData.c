#include "ReadSPIData.h"

/*
 * Function to set the SPI specs
 */
void SPI_Specs_Init()
{
	//Set desired pins
	SPI1_Example.SPI_Config.cs_gpio = GPIOA;
	SPI1_Example.SPI_Config.pin_clk = Pin5;
	SPI1_Example.SPI_Config.pin_miso = Pin6;
	SPI1_Example.SPI_Config.pin_mosi = Pin7;

	//Set desired transfer methods
	SPI1_Example.ssm = SSM_Enable;
	SPI1_Example.SPIx = SPI1;
	SPI1_Example.SPI_Config.baudrate_ctrl = DIV4;
	SPI1_Example.SPI_Config.cpha = Falling_Edge;
	SPI1_Example.SPI_Config.cpol = Even_Polarity;
	SPI1_Example.SPI_Config.data_format = MSB_First;
	SPI1_Example.data_frame = Data_8_Bits;
}

/*
 * @Brief	This function enables GPIO output mode, so the GPIO pin can act as a slave pin
 * 			to the accelerometer data.
 */
static void Slave_Pin_Init()
{
	//Create and initialze a slave pin with the desired port and pin
	GPIO_Config(&ADXL, GPIOA, Pin8, GPIO_Output, GPIO_PushPull, GPIO_LowSpeed, GPIO_PullUp);
	GPIO_Init(&ADXL, 0x0);
	GPIOA->ODR |= (1U << 8); //Used to enable the P-MOS and ensure CS is active high
}


void ReadADXLData(void *pvParameters)
{
	AccelerometerData data;

	uint8_t adxl_address[1] = {0xF2};	//Address of data register to read from
	uint8_t adxl_data_rec[7];			//Buffer to store the adxl data
	int16_t x, y, z;					//Variables that will store the data from the buffer

	/*
	 * Variables to initialize the ADXL registers: Set range to +- 4g, allow
	 * continous reading of the data registers and set the transfer rate to 100Hz.
	 */
	uint8_t adxl_set_data_format[2] = {0x31, 0x01};
	uint8_t adxl_clear_powerctl_reg[2] = {0x2D, 0x00};
	uint8_t adxl_set_powerctl_reg[2] = {0x2D, 0x08};
	uint8_t adxl_set_bw_rate_reg[2] = {0x2C, 0x0A};

	//Configure SPI and slave pin for ADXL
	Slave_Pin_Init();
	SPI_Specs_Init();
	SPI_Init(&SPI1_Example);

	/*
	 * Initial Transmission to configure ADXL with desired variables
	 */
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_clear_powerctl_reg, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_data_format, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_bw_rate_reg, 2);
	SPI_MultiSlave_TransmitIT(&SPI1_Example, &ADXL, adxl_set_powerctl_reg, 2);

	TickType_t _10ms = pdMS_TO_TICKS(5);

	while(1)
	{
		readingTask++;

		//Reading data from the SPI
		SPI_MultiSlave_RecieveIT(&SPI1_Example, &ADXL, adxl_data_rec, 7, *adxl_address);

		/*
		* Convert the data into usable/readable values - this can be found in the ADXL345 documentation,
		* and send the stored values to a queue.
		*/
		x = ((adxl_data_rec[2] << 8) | adxl_data_rec[1]);
		data.axis = x_axis;
		data.value = x;
		xQueueSend(adxl_data_queue, &data, _10ms);

		y = ((adxl_data_rec[4] << 8) | adxl_data_rec[3]);
		data.axis = y_axis;
		data.value = y;
		xQueueSend(adxl_data_queue, &data, _10ms);

		z = ((adxl_data_rec[6] << 8) | adxl_data_rec[5]);
		data.axis = z_axis;
		data.value = z;
		xQueueSend(adxl_data_queue, &data, _10ms);

	}

}

/*
 * Function to serve interrupts
 */
void SPI1_IRQHandler()
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	SPI_IRQ_Handler(&SPI1_Example);

	//Causes a context switch for the CPU
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


