#include "ReadSPIData.h"
#include "DataProcessing.h"
#include <stdio.h>


//int __io_putchar(int ch);


int main()
{
	UART_Config(&UART2, USART2, UART_MODE_TX, 115200);
	UART_Init(&UART2);

	data_queue = xQueueCreate(6, sizeof(AccelerometerData));  //Create queue to hold read data

	xTaskCreate(ReadADXLData, "Read ADXL Task", 1000, NULL, 1, NULL);
	xTaskCreate(DataProcessing, "Data Processing Task", 2000, NULL, 1, NULL);

	vTaskStartScheduler();

}


/*int __io_putchar(int ch)
{
	WriteByte(&UART2, (uint16_t)ch);
	return ch;
}*/

