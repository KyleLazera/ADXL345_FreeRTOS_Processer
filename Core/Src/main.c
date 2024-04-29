#include "ProgramInit.h"
#include "TIM3_Driver.h"
#include <stdio.h>


void SPI_Specs_Init();
void Slave_Pin_Init();
void UART2_Init();
void SPI1_Init();
void I2C1_Init();

int main()
{
	/*
	 **************************************************************
	 * Initialize Peripherals using stm32f4xx_periphDrivers
	 **************************************************************
	 */
	UART2_Init();
	SPI1_Init();
	TIM3Init();
	I2C1_Init();

	/*
	 **************************************************************
	 * Call FreeRTOS tasks
	 **************************************************************
	 */
	InitSemaphores();

	read_bme_sensor = xTimerCreate("Periodic Read", pdMS_TO_TICKS(200), pdTRUE, 0, ReadData);
	xTimerStart(read_bme_sensor, 0);

	print_data = xQueueCreate(10, sizeof(AccelerometerData));				//Queue to send data between PWM and print data
	adxl_data_queue = xQueueCreate(50, sizeof(AccelerometerData));  		//Create queue to hold read data
	filtered_data_queue = xQueueCreate(10, sizeof(AccelerometerData));		//Create queue to transmit the filtered data
	print_i2c_data = xQueueCreate(10, sizeof(BME_Values));
	send_raw_i2c = xQueueCreate(10, sizeof(bme_raw_array));

	ProgramInit();

	vTaskStartScheduler();


}

/*
 * @Brief	Initialize the SPI peripheral using peripheral drivers
 */
void SPI1_Init()
{
	SPI_Specs_Init();
	SPI_Init(&SPI1_Example);
	Slave_Pin_Init();
}


/*
 * @Brief	Initialize the UART peripheral using peripheral drivers
 */
void UART2_Init()
{
	UART_Config(&UART2, USART2, UART_MODE_TXRX, 115200);
	UART_Init(&UART2);
	UART_Interrupt_Init(&UART2, UART_RXNEIE_Enable);
	NVIC_SetPriority(USART2_IRQn, 5);
}

/*
 * @Brief	Initializes the I2C peripheral using the peripheral drivers
 */
void I2C1_Init()
{
	I2C_Config(&BME_Sensor, I2C1, SM_100KHZ, FM_DUTY_2, Pin8, Pin9);
	I2C_Init(&BME_Sensor);
}

/*
 * @Brief Function to set the SPI specs
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
void Slave_Pin_Init()
{
	//Create and initialze a slave pin with the desired port and pin
	GPIO_Config(&ADXL, GPIOA, Pin8, GPIO_Output, GPIO_PushPull, GPIO_LowSpeed, GPIO_PullUp);
	GPIO_Init(&ADXL, 0x0);
	GPIOA->ODR |= (1U << 8); //Used to enable the P-MOS and ensure CS is active high
}



