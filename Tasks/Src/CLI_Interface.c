#include "CLI_Interface.h"

/*
 *****************************************************
 *Global Variables
 *****************************************************
 */
FIFO_Buffer Command_Line_Buffer;

const char x_axis_[] = "xaxis\r";
const char y_axis_[] = "yaxis\r";
const char z_axis_[] = "zaxis\r";

/*
 * @Brief	Function used to compare the FIFO Buffer contents with pre-set messages.
 * @Note	This function will determine output based off CLI input
 */
static void CommandLineParser()
{
	if(strcmp(x_axis_, Command_Line_Buffer.buffer) == 0){
		axis_to_display = x_axis;
		ClearBuffer(&Command_Line_Buffer);}

	else if(strcmp(y_axis_, Command_Line_Buffer.buffer) == 0){
		axis_to_display = y_axis;
		ClearBuffer(&Command_Line_Buffer);}

	else if(strcmp(z_axis_, Command_Line_Buffer.buffer) == 0){
		axis_to_display = z_axis;
		ClearBuffer(&Command_Line_Buffer);}
}

/*
 * @Brief This will be the function passed into the thread
 */
void CommandLineRead()
{
	while(1)
	{
		cli_interface++;
		xSemaphoreTake(read_uart, portMAX_DELAY);

		CommandLineParser();
	}
}

/*
 * @Brief	Interrupt Service Routine for UART RXNE Flag
 */
void USART2_IRQHandler(void)
{
	if((USART2->SR) && (UART_SR_RXNE_Mask))
	{
		//Push value form UART RX Buffer into FIFIO Buffer
		if(Push(&Command_Line_Buffer, ReadByte(&UART2)))
		{
			BaseType_t xHigherPriorityTaskWoken = pdTRUE;

			//Give semaphore to enable main task to run
			xSemaphoreGiveFromISR(read_uart, &xHigherPriorityTaskWoken);

			//Causes a context switch for the CPU
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}

}
