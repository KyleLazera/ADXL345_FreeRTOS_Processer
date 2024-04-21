#include "CLI_Interface.h"

FIFO_Buffer Command_Line_Buffer;

static void CommandLineParser()
{
	if(strcmp("xaxis\r", Command_Line_Buffer.buffer) == 0){
		axis_to_display = x_axis;
		ClearBuffer(&Command_Line_Buffer);}

	else if(strcmp("yaxis\r", Command_Line_Buffer.buffer) == 0){
		axis_to_display = y_axis;
		ClearBuffer(&Command_Line_Buffer);}

	else if(strcmp("zaxis\r", Command_Line_Buffer.buffer) == 0){
		axis_to_display = z_axis;
		ClearBuffer(&Command_Line_Buffer);}
}


void CommandLineRead(void *pvParameters)
{
	axis_to_display = no_axis;

	while(1)
	{
		cli_interface++;
		xSemaphoreTake(read_uart, portMAX_DELAY);

		CommandLineParser();
	}
}

/*
 * @Brief	Interrupt Service Routine
 */
void USART2_IRQHandler(void)
{
	if((USART2->SR) && (UART_SR_RXNE_Mask))
	{
		//Push value form UART RX Buffer into FIFIO Buffer
		if(Push(&Command_Line_Buffer, ReadByte(&UART2)))
		{
			BaseType_t xHigherPriorityTaskWoken = pdTRUE;

			xSemaphoreGiveFromISR(read_uart, &xHigherPriorityTaskWoken);

			//Causes a context switch for the CPU
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}

}
