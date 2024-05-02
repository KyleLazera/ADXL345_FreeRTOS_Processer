#include "ProgramInit.h"

/*
 * @Brief	Function used to create tasks - calls the FreeRTOS xTaskCreate API function
 * @Note	This function just removes some of the params used by the xTaskCreate function which are
 * 			not used by this project specifically
 */
static uint8_t CreateTask(TaskFunction_t func_pointer, char *name, uint32_t stack_size, uint8_t priority)
{
	uint8_t success;
	TaskHandle_t handle;

	success = xTaskCreate(func_pointer, name, stack_size, NULL, priority, &handle);

	if(success == pdPASS)
		return 1;
	else
		return 0;

}

/*
 * @Brief	This function creates the semaphores to be used by the RTOS
 */
void InitSemaphores()
{
	//Controls flow of CLI task
	read_uart = xSemaphoreCreateBinary();
	//Controls flow of reading SPI data
	read_spi = xSemaphoreCreateBinary();
	read_i2c = xSemaphoreCreateBinary();
	i2c_succesful_read = xSemaphoreCreateBinary();
}

/*
 * @Brief	Function used to initialize and create queues based off handles
 */
void InitQueues()
{
	print_data = xQueueCreate(10, sizeof(AccelerometerData));				//Queue to send data between PWM and print data
	adxl_data_queue = xQueueCreate(50, sizeof(AccelerometerData));  		//Create queue to hold read data
	filtered_data_queue = xQueueCreate(20, sizeof(AccelerometerData));		//Create queue to transmit the filtered data
	print_i2c_data = xQueueCreate(20, sizeof(BME_Values));					//Create queue to receive and send compensated i2c data
	send_raw_i2c = xQueueCreate(10, sizeof(bme_raw_array));					//Create queue to receive and send the raw i2c data
}

/*
 * @Brief	Function to initialize a timer(s) used in the application
 */
void InitTimer()
{
	read_bme_sensor = xTimerCreate("Periodic Read", pdMS_TO_TICKS(200), pdTRUE, 0, ReadData);
	xTimerStart(read_bme_sensor, 0);
}

/*
 * @Brief	This is the initializer function that creates all the tasks. Called from main function.
 */
void ProgramInit()
{

	CreateTask(CommandLineRead, "Read UART", STACK_SIZE_200, PRIORITY_4);
	CreateTask(ReadADXLData, "Read ADXL345 Data", STACK_SIZE_500, PRIORITY_3);
	CreateTask(DataProcessing, "Filter Raw Data", STACK_SIZE_1000, PRIORITY_2);
	CreateTask(UART_GateKeeper, "Print Filtered Data", STACK_SIZE_500, PRIORITY_1);
	CreateTask(DisplayData_PWM, "PWM of Data", STACK_SIZE_200, PRIORITY_1);
	CreateTask(BME_Data_Calculation, "Compute BME data", STACK_SIZE_200, PRIORITY_2);

}
