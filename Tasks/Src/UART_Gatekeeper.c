#include "UART_Gatekeeper.h"


void UART_GateKeeper(void *pvParameters)
{
	AccelerometerData filtered_data;
	BME_Values compensated_data;

	while(1)
	{
		gatekeeper++;

		xQueueReceive(filtered_data_queue, &filtered_data, 0);
		//xQueueReceive(print_i2c_data, &compensated_data, 0);

		if(filtered_data.axis == axis_to_display)
		{
			printf("%.2f\n\r", filtered_data.value);
		}

		xQueueSend(print_data, &filtered_data, _10ms);

	}
}



