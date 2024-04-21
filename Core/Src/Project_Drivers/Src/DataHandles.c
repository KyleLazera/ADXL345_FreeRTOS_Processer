#include "DataHandles.h"

/*
 ***********************************************************
 * Global Peripheral Handles
 ***********************************************************
 */
SPI_Handle_t SPI1_Example;
GPIO_Config_t ADXL;
UART_Config_t UART2;

/*
 ***********************************************************
 * FreeRTOS Global Variables
 ***********************************************************
 */

QueueHandle_t adxl_data_queue, filtered_data_queue, print_data;
SemaphoreHandle_t read_uart, read_spi;

TickType_t _5ms = pdMS_TO_TICKS(5);
TickType_t _10ms = pdMS_TO_TICKS(10);
/*
 ************************************************************
 * Global Variables
 ************************************************************
 */

int readingTask, filterTask, gatekeeper, cli_interface, pwm_count;
AxisOfRotation axis_to_display = no_axis;

/*
 ************************************************************
 * Function Definitions
 ************************************************************
 */

/*
 * @Brief	Re-target printf top use with UART
 */
int __io_putchar(int ch)
{
	WriteByte(&UART2, (uint16_t)ch);
	return ch;
}



