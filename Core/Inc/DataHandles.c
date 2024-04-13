#include "DataHandles.h"

SPI_Handle_t SPI1_Example;
GPIO_Config_t ADXL;
UART_Config_t UART2;

QueueHandle_t adxl_data_queue, filtered_data_queue;


int __io_putchar(int ch)
{
	WriteByte(&UART2, (uint16_t)ch);
	return ch;
}
