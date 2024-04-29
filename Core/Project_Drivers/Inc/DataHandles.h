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
extern TimerHandle_t read_bme_sensor;

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
 *	Temperature/Pressure/Humidity Sensor Data Structure
 ***********************************************************
 */

typedef struct
{
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;

	uint16_t dig_P1;
	int16_t dig_Px[8];
}BME_Comp_Value_t;

typedef struct
{
	float temperature;
	float pressure;
	float humidity;
	BME_Comp_Value_t Compensation_Vals;
}BME_Values;

/*
 ************************************************************
 * Global Variables/Data Structures
 ************************************************************
 */

typedef struct{
	AccelerometerData acc_data;
	BME_Values bme_data;
}Sensor_Data;

extern AxisOfRotation axis_to_display;
extern int readingTask, filterTask, gatekeeper, cli_interface, pwm_count, i2c_count, comp_count;
typedef uint8_t bme_raw_array[9];

/*
 **************************************************************
 * Functions
 **************************************************************
 */

int __io_putchar(int ch);

#endif /* INC_DATAHANDLES_H_ */
