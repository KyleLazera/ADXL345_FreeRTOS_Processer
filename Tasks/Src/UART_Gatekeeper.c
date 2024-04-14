#include "UART_Gatekeeper.h"

void PrintFilteredData(void *pvParameters)
{
	AccelerometerData filtered_data;

	while(1)
	{
		gatekeeper++;

		xQueueReceive(filtered_data_queue, &filtered_data, 0);

		if(filtered_data.axis == x_axis)
		{
			printf("%.2f\n\r", filtered_data.value);
		}

	}
}

