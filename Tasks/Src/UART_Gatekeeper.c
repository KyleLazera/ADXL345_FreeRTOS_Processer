#include "UART_Gatekeeper.h"

/*
 * @Brief	Function holds control over the UART and is the sole thread that can print values to the serial communication port
 */
void UART_GateKeeper(void *pvParameters)
{
	AccelerometerData filtered_data;
	BME_Values compensated_data;

	while(1)
	{
		gatekeeper++;

		//Receive values from the data processing thread
		xQueueReceive(filtered_data_queue, &filtered_data, 0);

		//Check to see if the user has specified an axis to display - if so print the value
		if(filtered_data.axis == axis_to_display)
		{
			printf("%.2f\n\r", filtered_data.value);
		}

		//If the user has chosen to specify the temperature, display the temperature
		else if(axis_to_display == no_axis && value_to_display == temperature)
		{
			/*
			 * The data from the I2C value will only read values from the queue if the user specifies it needs to read
			 * the temperature.
			 */
			xQueueReceive(print_i2c_data, &compensated_data, 0);

			/*
			 * Keep a counter to print the values after every 500 ticks in the task. This prevents a large amount of the same valued data being output
			 * at once.
			 */
			if((gatekeeper % 500) == 0){
				printf("%d\n\r", compensated_data.temperature);}
		}

		//Send data to the pulse width modulation thread
		xQueueSend(print_data, &filtered_data, _10ms);

	}
}



