#include "UART_Gatekeeper.h"


void UART_GateKeeper(void *pvParameters)
{
	AccelerometerData filtered_data;
	BME_Values compensated_data;

	int32_t current_value;

	while(1)
	{
		gatekeeper++;

		xQueueReceive(filtered_data_queue, &filtered_data, 0);

		if(filtered_data.axis == axis_to_display)
		{
			printf("%.2f\n\r", filtered_data.value);
		}

		else if(axis_to_display == no_axis && value_to_display == temperature)
		{
			xQueueReceive(print_i2c_data, &compensated_data, 0);

			/*
			 * Keep a counter to print the values after every 500 ticks in the task. This prevents a large amount of the same valued data being output
			 * at once.
			 */
			if((gatekeeper % 500) == 0){
				printf("%d\n\r", compensated_data.temperature);}
		}

		xQueueSend(print_data, &filtered_data, _10ms);

	}
}



