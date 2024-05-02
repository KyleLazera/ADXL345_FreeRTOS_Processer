#include "DataHandles.h"

/*
 ***********************************************************
 * Global Peripheral Handles
 ***********************************************************
 */
SPI_Handle_t SPI1_Example;
GPIO_Config_t ADXL;
UART_Config_t UART2;
I2C_Handle_t BME_Sensor;

/*
 ***********************************************************
 * FreeRTOS Global Variables
 ***********************************************************
 */

QueueHandle_t adxl_data_queue, filtered_data_queue, print_data, print_i2c_data, send_raw_i2c;
SemaphoreHandle_t read_uart, read_spi, read_i2c, i2c_succesful_read;
TimerHandle_t read_bme_sensor;

TickType_t _5ms = pdMS_TO_TICKS(5);
TickType_t _10ms = pdMS_TO_TICKS(10);
TickType_t _100ms = pdMS_TO_TICKS(100);
/*
 ************************************************************
 * Global Variables
 ************************************************************
 */

int readingTask, filterTask, gatekeeper, cli_interface, pwm_count, i2c_count, comp_count;
AxisOfRotation axis_to_display = no_axis;
BMEDisplayValue value_to_display;

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



