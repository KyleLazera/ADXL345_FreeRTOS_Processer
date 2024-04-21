#include "PulseWidthMod_Output.h"

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

void DisplayData_PWM(void *pvParameters)
{
	AccelerometerData rec_data;

	while(1)
	{
		xQueueReceive(print_data, &rec_data, 0);
		pwm_count++;

		switch(rec_data.axis)
		{
		case no_axis:
			break;

		case x_axis:
			SetDutyCycle(1, (int)rec_data.value);
			break;

		case y_axis:
			SetDutyCycle(2, (int)rec_data.value);
			break;

		case z_axis:
			SetDutyCycle(4, (int)rec_data.value);
			break;
		}
	}
}


