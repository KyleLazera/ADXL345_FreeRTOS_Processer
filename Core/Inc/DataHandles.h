#ifndef INC_DATAHANDLES_H_
#define INC_DATAHANDLES_H_

#include "cmsis_os.h"
#include "stm32f401_spi.h"

extern SPI_Handle_t SPI1_Example;
extern GPIO_Config_t ADXL;
extern UART_Config_t UART2;

extern QueueHandle_t data_queue;

int __io_putchar(int ch);

typedef enum
{
	x_axis,
	y_axis,
	z_axis
}AxisOfRotation;

typedef struct
{
	AxisOfRotation axis;
	int16_t value;
}AccelerometerData;


#endif /* INC_DATAHANDLES_H_ */
