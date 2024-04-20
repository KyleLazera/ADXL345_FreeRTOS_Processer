#include "CLI_Interface.h"

void CommandLineRead(void *pvParameters)
{
	int i = 0;

	while(1)
	{
		cli_interface++;
		xSemaphoreTake(read_uart, portMAX_DELAY);

		buffer[i] = ReadByte(&UART2);
		i = (i + 1) % 10;
		//printf("Read UART\n\r");
	}
}

/*
 * @Brief	Interrupt Service Routine
 */
void USART2_IRQHandler(void)
{
	if((USART2->SR) && (UART_SR_RXNE_Mask))
	{
		USART2->SR |= (0U << 5);

		BaseType_t xHigherPriorityTaskWoken = pdTRUE;

		xSemaphoreGiveFromISR(read_uart, &xHigherPriorityTaskWoken);

		//Causes a context switch for the CPU
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}

}
