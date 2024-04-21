#include "UART_Gatekeeper.h"


void UART_GateKeeper(void *pvParameters)
{
	AccelerometerData filtered_data;
	TickType_t _10ms = pdMS_TO_TICKS(10);

	while(1)
	{
		//xSemaphoreTake(print_data, _10ms);
		gatekeeper++;

		xQueueReceive(filtered_data_queue, &filtered_data, 0);

		if(filtered_data.axis == axis_to_display)
		{
			printf("%.2f\n\r", filtered_data.value);
		}

		xQueueSend(print_data, &filtered_data, _10ms);

	}
}



