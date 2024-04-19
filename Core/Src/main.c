#include "ReadSPIData.h"
#include "DataProcessing.h"
#include "UART_Gatekeeper.h"
#include <stdio.h>

int main()
{
	/*
	 **************************************************************
	 * Initialize Peripherals using stm32f4xx_periphDrivers
	 **************************************************************
	 */
	UART_Config(&UART2, USART2, UART_MODE_TX, 115200);
	UART_Init(&UART2);

	adxl_data_queue = xQueueCreate(50, sizeof(AccelerometerData));  		//Create queue to hold read data
	filtered_data_queue = xQueueCreate(10, sizeof(AccelerometerData));	//Create queue to transmit the filtered data

	xTaskCreate(DataProcessing, "Data Processing Task", 2000, NULL, 2, NULL);
	xTaskCreate(OutputData, "Print Filtered Data", 500, NULL, 1, NULL);
	xTaskCreate(ReadADXLData, "Read ADXL Task", 1000, NULL, 3, NULL);

	vTaskStartScheduler();

}

