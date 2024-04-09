#ifndef INC_DATAPROCESSING_H_
#define INC_DATAPROCESSING_H_

#include "DataHandles.h"

#define FILTER_ORDER		7

static float FILTER_COEFFICIENTS[(FILTER_ORDER * 2) + 1] = {};

typedef struct
{
	//Initialize 2 FIFO buffers to hold the data
	float moving_avg_buffer[FILTER_ORDER + 1];
	float recursive_buffer[FILTER_ORDER];
	//Define the head for the FIFO Buffers
	uint8_t input_front, recursive_front;

	float moving_avg_result, recursive_result;
	float output;

}LowPass_Filter;

void DataProcessing(void *pvParameters);


#endif /* INC_DATAPROCESSING_H_ */
