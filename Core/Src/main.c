#include "cmsis_os.h"
#include "stm32f401_spi.h"

int count1, count2;

void Task1(void *pvParameters);
void Task2(void *pvParameters);

int main()
{

	xTaskCreate(Task1, "Demo1", 100, NULL, 1, NULL);
	xTaskCreate(Task2, "Demo2", 100, NULL, 1, NULL);

	vTaskStartScheduler();

	while(1)
	{

	}
}

void Task1(void *pvParameters)
{
	while(1)
	{
		count1++;
	}
}

void Task2(void *pvParameters)
{

	while(1)
	{
		count2++;
	}
}
