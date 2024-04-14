#include "ReadSPIData.h"
#include "DataProcessing.h"
#include "UART_Gatekeeper.h"
#include <stdio.h>


int main()
{
	UART_Config(&UART2, USART2, UART_MODE_TX, 115200);
	UART_Init(&UART2);

	adxl_data_queue = xQueueCreate(50, sizeof(AccelerometerData));  		//Create queue to hold read data
	filtered_data_queue = xQueueCreate(6, sizeof(AccelerometerData));	//Create queue to transmit the filtered data

	xCountingSemaphore = xSemaphoreCreateCounting(300, 0);		//params are max count and initial count

	xTaskCreate(ReadADXLData, "Read ADXL Task", 1000, NULL, 3, NULL);
	xTaskCreate(DataProcessing, "Data Processing Task", 2000, NULL, 2, NULL);
	xTaskCreate(PrintFilteredData, "Print Filtered Data", 500, NULL, 1, NULL);

	vTaskStartScheduler();

}


