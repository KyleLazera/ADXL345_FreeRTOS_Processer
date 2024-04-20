#include "ReadSPIData.h"
#include "DataProcessing.h"
#include "UART_Gatekeeper.h"
#include "CLI_Interface.h"
#include <stdio.h>

void SPI_Specs_Init();
void Slave_Pin_Init();
void Tim3_PWM_Init(uint8_t channel);
void Tim3Init();

int main()
{
	/*
	 **************************************************************
	 * Initialize Peripherals using stm32f4xx_periphDrivers
	 **************************************************************
	 */
	UART_Config(&UART2, USART2, UART_MODE_TXRX, 115200);
	UART_Init(&UART2);
	UART_Interrupt_Init(&UART2, UART_RXNEIE_Enable);
	NVIC_SetPriority(USART2_IRQn, 6);

	SPI_Specs_Init();
	SPI_Init(&SPI1_Example);
	Slave_Pin_Init();

	Tim3Init();

	/*
	 **************************************************************
	 * Call FreeRTOS tasks
	 **************************************************************
	 */
	read_uart = xSemaphoreCreateBinary();
	read_spi = xSemaphoreCreateBinary();

	adxl_data_queue = xQueueCreate(50, sizeof(AccelerometerData));  		//Create queue to hold read data
	filtered_data_queue = xQueueCreate(10, sizeof(AccelerometerData));		//Create queue to transmit the filtered data

	xTaskCreate(CommandLineRead, "Read UART", 1000, NULL, 4, NULL);
	xTaskCreate(ReadADXLData, "Read ADXL Task", 1000, NULL, 3, NULL);
	xTaskCreate(DataProcessing, "Data Processing Task", 1000, NULL, 2, NULL);
	xTaskCreate(OutputData, "Print Filtered Data", 500, NULL, 1, NULL);

	vTaskStartScheduler();

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

void Tim3_PWM_Init(uint8_t channel)
{
	TIM3->CR1 |= CR1_ARPE_Enable;

	switch(channel)
	{
	case 1:
		TIM3->CCER |= CapComp1_Enable;
		TIM3->CCMR1 |= OCM1_PWM_Mode | OCPE1_Enable;
		break;

	case 2:
		TIM3->CCER |= CapComp2_Enable;
		TIM3->CCMR1 |= OCM2_PWM_Mode | OCPE2_Enable;
		break;

	case 4:
		TIM3->CCER |= CapComp4_Enable;
		TIM3->CCMR2 |= OCM4_PWM_Mode | OCPE4_Enable;
		break;
	}
}

void Tim3Init()
{
	GPIO_Config_t x_axis, y_axis, z_axis;

	//Enable Clock Access to TIM2
	RCC_APB1Cmd(TIM3_Enable, ENABLE);

	//Init the output ports for ouput compare mode
	GPIO_Config(&x_axis, GPIOC, Pin6, GPIO_AF, GPIO_PushPull, GPIO_MediumSpeed, GPIO_PUPD_None);
	GPIO_Init(&x_axis, AF2);

	GPIO_Config(&y_axis, GPIOC, Pin7, GPIO_AF, GPIO_PushPull, GPIO_MediumSpeed, GPIO_PUPD_None);
	GPIO_Init(&y_axis, AF2);

	GPIO_Config(&z_axis, GPIOC, Pin9, GPIO_AF, GPIO_PushPull, GPIO_MediumSpeed, GPIO_PUPD_None);
	GPIO_Init(&z_axis, AF2);

	//Enable PWM mode on the specified channels
	Tim3_PWM_Init(1);
	Tim3_PWM_Init(2);
	Tim3_PWM_Init(4);

	//Set Prescaler and value to count to
	TIM3->PSC = 16;
	TIM3->ARR = 150;

	//Enable the TIM2
	TIM3->EGR |= EGR_Enable;
	TIM3->CR1 |= CR1_CEN;

}
