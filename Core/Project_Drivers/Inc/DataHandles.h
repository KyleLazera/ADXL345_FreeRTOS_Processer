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
extern I2C_Handle_t BME_Sensor;;

/*
 ***********************************************************
 * Declare FreeRTOS Global Variables ie. Semaphores, Qeues etc.
 ***********************************************************
 */
extern QueueHandle_t adxl_data_queue, filtered_data_queue, print_data, print_i2c_data, send_raw_i2c;
extern SemaphoreHandle_t read_uart, read_spi, read_i2c;
extern SemaphoreHandle_t read_uart, read_spi, read_i2c, i2c_succesful_read;
extern TimerHandle_t read_bme_sensor;

extern TickType_t _5ms, _10ms, _100ms;

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
 *	Temperature/Pressure/Humidity Sensor Data Structure
 ***********************************************************
 */

//Enum to keep track of which value to display based on serial port input
typedef enum
{
	no_value,
	temperature,
	pressure,
}BMEDisplayValue;

typedef struct
{
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;

	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
}BME_Comp_Value_t;

typedef struct
{
	int32_t temperature;
	int32_t pressure;
	BME_Comp_Value_t Compensation_Vals;
}BME_Values;

/*
 ************************************************************
 * Global Variables/Data Structures
 ************************************************************
 */


extern AxisOfRotation axis_to_display;
extern BMEDisplayValue value_to_display;
extern int readingTask, filterTask, gatekeeper, cli_interface, pwm_count, i2c_count, comp_count;
typedef uint8_t bme_raw_array[9];

/*
 **************************************************************
 * Functions
 **************************************************************
 */

int __io_putchar(int ch);

#endif /* INC_DATAHANDLES_H_ */
