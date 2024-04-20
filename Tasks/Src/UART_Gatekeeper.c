#include "UART_Gatekeeper.h"


static void SetDutyCycle(uint8_t channel, int value)
{
	if(value < 0)
	{
		value *= (-1);
	}

	switch(channel)
	{
	case 1:
		TIM3->CCR1 = value;
		break;

	case 2:
		TIM3->CCR2 = value;
		break;

	case 4:
		TIM3->CCR4 = value;
		break;
	}
}


void OutputData(void *pvParameters)
{
	AccelerometerData filtered_data;

	while(1)
	{
		gatekeeper++;

		xQueueReceive(filtered_data_queue, &filtered_data, 0);

		switch(filtered_data.axis)
		{
		case x_axis:
			printf("%.2f\n\r", filtered_data.value);
			SetDutyCycle(1, (int)filtered_data.value);
			break;

		case y_axis:

			//printf("%.2f\n\r", filtered_data.value);
			SetDutyCycle(2, (int)filtered_data.value);
			break;

		case z_axis:

			//printf("%.2f\n\r", filtered_data.value);
			SetDutyCycle(4, (int)filtered_data.value);
			break;
		}

	}
}



