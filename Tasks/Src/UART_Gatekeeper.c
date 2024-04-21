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

		if(filtered_data.axis == x_axis )
		{
			if(axis_to_display == x_axis)
				printf("%.2f\n\r", filtered_data.value);
			SetDutyCycle(1, (int)filtered_data.value);
		}

		if(filtered_data.axis == y_axis)
		{
			if(axis_to_display == y_axis)
				printf("%.2f\n\r", filtered_data.value);
			SetDutyCycle(1, (int)filtered_data.value);
		}

		if(filtered_data.axis == z_axis)
		{
			if(axis_to_display == z_axis)
				printf("%.2f\n\r", filtered_data.value);
			SetDutyCycle(1, (int)filtered_data.value);
		}

	}
}



