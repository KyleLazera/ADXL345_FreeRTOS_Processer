#include "DataProcessing.h"

static void ReadDataQueue(AccelerometerData *rec_data)
{
	int16_t _x, _y, _z;

	xQueueReceive(data_queue, rec_data, 0);

	switch(rec_data->axis)
	{
	case x_axis:
		_x = rec_data->value;
		break;
	case y_axis:
		_y = rec_data->value;
		break;
	case z_axis:
		_z = rec_data->value;
		break;
	}

	//printf("%d\n\r", _x);
}

/*
 * Initialize the filter prior to beginning computation.
 */
static void InitFilter(LowPass_Filter *filter)
{
	//Clear the FIFO buffers
	for(int index = 0; index <= FILTER_ORDER; index++)
	{
		filter->moving_avg_buffer[index] = 0.0f;
		filter->recursive_buffer[index] = 0.0f;
	}

	//Ensure the head of the FIFO is starting at index 0
	filter->front = 0;

	//Set the initial outputs to zero
	filter->moving_avg_result = 0.0f;
	filter->recursive_result = 0.0f;
	filter->output = 0.0f;
}

static float FilterCompuation(LowPass_Filter *filter, float input)
{
	//Store the current input in the input FIFO
	filter->moving_avg_buffer[filter->input_front] = input;

	//Increment the front of the FIFO and ensure it wraps around forming a circular buffer
	filter->input_front = (filter->input_front + 1) % (FILTER_ORDER+1);

	//Store the current output in the recursive buffer
	filter->recursive_buffer[filter->recursive_front] = filter->output;

	//Increment the front of the FIFO and esnure it is circular
	filter->recursive_front = (filter->recursive_front + 1) % (FILTER_ORDER);

	//Convolution for running sum portion
	for(int i = 0; i < FILTER_ORDER + 1; i++)
	{

	}
}

void DataProcessing(void *pvParameters)
{
	AccelerometerData rec_data;
	LowPass_Filter EllipticLP;

	InitFilter(&EllipticLP);

	while(1)
	{
		ReadDataQueue(&rec_data);			//Read accelerometer data from FreeRTOS queue

		if(rec_data.axis == x_axis)
		{
			printf("%d\n\r", rec_data.value);
		}

	}
}


