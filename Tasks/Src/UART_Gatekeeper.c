#include "UART_Gatekeeper.h"

static void Tim3_PWM_Init(uint8_t channel)
{
	TIM3->CR1 |= CR1_ARPE_Enable;

	switch(channel)
	{
	case 1:
		TIM3->CCER |= CapComp1_Enable;
		TIM3->CCMR1 |= OCM1_PWM_Mode | OCPE1_Enable;
		break;

	case 2:
		TIM3->CCER |= CapComp2_Enable;
		TIM3->CCMR1 |= OCM2_PWM_Mode | OCPE2_Enable;
		break;

	case 4:
		TIM3->CCER |= CapComp4_Enable;
		TIM3->CCMR2 |= OCM4_PWM_Mode | OCPE4_Enable;
		break;
	}
}

static void Tim3Init()
{
	GPIO_Config_t x_axis, y_axis, z_axis;

	//Enable Clock Access to TIM2
	RCC_APB1Cmd(TIM3_Enable, ENABLE);

	//Init the output ports for ouput compare mode
	GPIO_Config(&x_axis, GPIOC, Pin6, GPIO_AF, GPIO_PushPull, GPIO_MediumSpeed, GPIO_PUPD_None);
	GPIO_Init(&x_axis, AF2);

	GPIO_Config(&y_axis, GPIOC, Pin7, GPIO_AF, GPIO_PushPull, GPIO_MediumSpeed, GPIO_PUPD_None);
	GPIO_Init(&y_axis, AF2);

	GPIO_Config(&z_axis, GPIOC, Pin9, GPIO_AF, GPIO_PushPull, GPIO_MediumSpeed, GPIO_PUPD_None);
	GPIO_Init(&z_axis, AF2);

	//Enable PWM mode on the specified channels
	Tim3_PWM_Init(1);
	Tim3_PWM_Init(2);
	Tim3_PWM_Init(4);

	//Set Prescaler and value to count to
	TIM3->PSC = 16;
	TIM3->ARR = 300;

	//Enable the TIM2
	TIM3->EGR |= EGR_Enable;
	TIM3->CR1 |= CR1_CEN;

}

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

	int initial_x_value, initial_y_value, initial_z_value, duty_cycle;

	static bool initial_x_value_set = false, initial_y_value_set = false, initial_z_value_set = false;

	Tim3Init();

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

