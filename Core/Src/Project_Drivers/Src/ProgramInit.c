#include "ProgramInit.h"

/*
 * @Brief	Function used to create tasks - calls the FreeRTOS xTaskCreate API function
 * @Note	This function just removes some of the params used by the xTaskCreate function which are
 * 			not used by this project specifically
 */
static uint8_t CreateTask(TaskFunction_t func_pointer, char *name, uint32_t stack_size, uint8_t priority)
{
	uint8_t success;

	success = xTaskCreate(func_pointer, name, stack_size, NULL, priority, NULL);

	if(success == pdPASS)
		return 1;
	else
		return 0;

}

/*
 * @Brief	This is the initializer function that creates all the tasks. Called from main function.
 * @retval	Function returns a checksum indicating how many tasks were successfully created
 */
uint8_t ProgramInit()
{
	uint8_t checksum = 0;

	checksum += CreateTask(CommandLineRead, "Read UART", STACK_SIZE_500, PRIORITY_4);
	checksum += CreateTask(ReadADXLData, "Read ADXL345 Data", STACK_SIZE_1000, PRIORITY_3);
	checksum += CreateTask(DataProcessing, "Filter Raw Data", STACK_SIZE_1000, PRIORITY_2);
	checksum += CreateTask(UART_GateKeeper, "Print Filtered Data", STACK_SIZE_500, PRIORITY_1);
	checksum += CreateTask(DisplayData_PWM, "PWM of Data", STACK_SIZE_200, PRIORITY_1);

	return checksum;
}
