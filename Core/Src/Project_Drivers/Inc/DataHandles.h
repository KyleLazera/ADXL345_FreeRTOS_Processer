#ifndef INC_DATAHANDLES_H_
#define INC_DATAHANDLES_H_

#include "cmsis_os.h"
#include "stm32f401_spi.h"
#include "stdbool.h"

/*
 ***********************************************************
 * Declare Global Peripheral Handles
 ***********************************************************
 */
extern SPI_Handle_t SPI1_Example;
extern GPIO_Config_t ADXL;
extern UART_Config_t UART2;

/*
 ***********************************************************
 * Declare FreeRTOS Global Variables ie. Semaphores, Qeues etc.
 ***********************************************************
 */
extern QueueHandle_t adxl_data_queue, filtered_data_queue, print_data;
extern SemaphoreHandle_t read_uart, read_spi;

extern TickType_t _5ms, _10ms;

/*
 ***********************************************************
 * Accelerometer Data Structure
 ***********************************************************
 */

typedef enum
{
	no_axis,
	x_axis,
	y_axis,
	z_axis,
}AxisOfRotation;

typedef struct
{
	AxisOfRotation axis;
	float value;
}AccelerometerData;

/*
 ************************************************************
 * Global Variables
 ************************************************************
 */

extern AxisOfRotation axis_to_display;
extern int readingTask, filterTask, gatekeeper, cli_interface, pwm_count;


/*
 **************************************************************
 * Functions
 **************************************************************
 */

int __io_putchar(int ch);

#endif /* INC_DATAHANDLES_H_ */
