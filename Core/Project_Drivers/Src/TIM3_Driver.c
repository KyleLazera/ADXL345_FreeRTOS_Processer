#include "TIM3_Driver.h"

static void TIM3_PWM_Init(uint8_t channel)
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

/*
 * @Brief Initialize TIM3 with GPIO pins and channels
 */
void TIM3Init()
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
	TIM3_PWM_Init(1);
	TIM3_PWM_Init(2);
	TIM3_PWM_Init(4);

	//Set Prescaler and value to count to
	//TODO: Create pre-Processor directives for these values
	TIM3->PSC = 16;
	TIM3->ARR = 150;

	//Enable the TIM2
	TIM3->EGR |= EGR_Enable;
	TIM3->CR1 |= CR1_CEN;

}


