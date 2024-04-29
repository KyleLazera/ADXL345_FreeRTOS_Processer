#include "CLI_Interface.h"

/*
 *****************************************************
 *Global Variables
 *****************************************************
 */
FIFO_Buffer Command_Line_Buffer;

/*
 * @Brief	Function used to compare the FIFO Buffer contents with pre-set messages.
 * @Note	This function will determine output based off CLI input
 */
static void CommandLineParser()
{
	if(strcmp("xaxis\r", Command_Line_Buffer.buffer) == 0){
		axis_to_display = x_axis;
		value_to_display = no_value;
		ClearBuffer(&Command_Line_Buffer);}

	else if(strcmp("yaxis\r", Command_Line_Buffer.buffer) == 0){
		axis_to_display = y_axis;
		value_to_display = no_value;
		ClearBuffer(&Command_Line_Buffer);}

	else if(strcmp("zaxis\r", Command_Line_Buffer.buffer) == 0){
		axis_to_display = z_axis;
		value_to_display = no_value;
		ClearBuffer(&Command_Line_Buffer);}

	else if(strcmp("stop\r", Command_Line_Buffer.buffer) == 0){
		axis_to_display = no_axis;
		value_to_display = no_value;
		ClearBuffer(&Command_Line_Buffer);}

	else if(strcmp("temp\r", Command_Line_Buffer.buffer) == 0){
		axis_to_display = no_axis;
		value_to_display = temperature;
		ClearBuffer(&Command_Line_Buffer);}

	//This is used for a default value to clear the buffer
	else if (strcmp("\r", Command_Line_Buffer.buffer) == 0){
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
		//This semaphore prevents the task from running until a UART interrupt occurs
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

			//Causes a context switch for the CPU to the highest task
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
	}

}
