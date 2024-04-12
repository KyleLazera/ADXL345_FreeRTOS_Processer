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
 * Initialize an FIR filter
 */
static void InitFIRFilter(FIR_LowPass_Filter *filter)
{
	//Clear the FIFO buffers
	for(int index = 0; index <= FIR_FILTER_ORDER; index++)
	{
		filter->moving_avg_buffer[index] = 0.0f;
	}

	//Ensure the head of the FIFO is starting at index 0
	filter->input_front = 0;

	filter->output = 0.0f;

}

/*
 * Initialize a cascade for the IIR filter implementation
 */
static void InitCascade(IIR_LowPass_Filter *filter, float num_coeff[], float denom_coeff[], int order, float gain)
{
	//Initialize buffer values to 0
	for(int i = 0; i < 2; i++)
	{
		filter->buffer[i] = 0;
	}

	for(int i = 0; i < order; i++)
	{
		//Initialize Coefficients for denominator
		filter->denominator_coefficients[i] = denom_coeff[i];
	}

	for(int i = 0; i < order + 1; i++)
	{
		//Initialize Coefficients for denominator
		filter->numerator_coefficients[i] = num_coeff[i];
	}

	filter->gain = gain;
}

/*
 * AlgorIthm to run the cascade
 */
static float CascadeIIR(IIR_LowPass_Filter *filter, int16_t input)
{
	//Intermediate value
	float w = (float)input - (filter->buffer[0] - filter->denominator_coefficients[0]) - (filter->buffer[1] - filter->denominator_coefficients[1]);
	//Output value
	float output = (w * filter->numerator_coefficients[0]) + (filter->buffer[0] * filter->numerator_coefficients[1]) + (filter->buffer[1] * filter->numerator_coefficients[2]);
	output *= filter->gain;
	//Shift buffer values (delay)
	filter->buffer[1] = filter->buffer[0];
	filter->buffer[0] = output;

	return output;
}

static float FIRFilterComputation(FIR_LowPass_Filter *filter, int16_t input)
{
	uint8_t indexCounter;

	//Store the current input in the input FIFO
	filter->moving_avg_buffer[filter->input_front] = (float)input;

	//Increment the head of the FIFO and ensure it wraps around forming a circular buffer
	//filter->input_front = (filter->input_front + 1) % (FILTER_ORDER + 1);
	filter->input_front++;
	if(filter->input_front > FIR_FILTER_ORDER)
	{
		filter->input_front = 0;
	}

	indexCounter = filter->input_front;
	filter->output = 0.0f;

	//Convolution for running sum portion
	for(int i = 0; i <= FIR_FILTER_ORDER; i++)
	{
		//Retrieve the input values from the FIFO Buffer
		if(indexCounter == 0)
		{
			indexCounter = FIR_FILTER_ORDER;
		}
		else
		{
			indexCounter--;
		}

		//Multiply value by the filter coefficient
		filter->output += (filter->moving_avg_buffer[indexCounter]) * (FIR_FILTER_COEFFICIENTS[i]);
	}

	return filter->output;
}

void DataProcessing(void *pvParameters)
{
	AccelerometerData rec_data;
	FIR_LowPass_Filter EllipticLP;
	int16_t input = 0;
	float output;

	IIR_LowPass_Filter cascade1, cascade2, cascade3;

	InitCascade(&cascade1, NUMERATOR_CASCADE1_COEFFICIENTS, DENOMINATOR_CASCADE1_COEFFICIENTS, IIR_FILTER_ORDER, GAIN_CASCADE1);
	InitCascade(&cascade2, NUMERATOR_CASCADE2_COEFFICIENTS, DENOMINATOR_CASCADE2_COEFFICIENTS, IIR_FILTER_ORDER, GAIN_CASCADE2);
	InitCascade(&cascade3, NUMERATOR_CASCADE3_COEFFICIENTS, DENOMINATOR_CASCADE3_COEFFICIENTS, IIR_FILTER_ORDER, GAIN_CASCADE3);

	//InitFIRFilter(&EllipticLP);

	while(1)
	{
		ReadDataQueue(&rec_data);			//Read accelerometer data from FreeRTOS queue

		if(rec_data.axis == x_axis)
		{
			input = rec_data.value;
			//FIRFilterComputation(&EllipticLP, input);
			output = CascadeIIR(&cascade1, input);
			output = CascadeIIR(&cascade1, output);
			output = CascadeIIR(&cascade1, output);
			printf("%d, %.2f\n\r", input, output);
		}
	}
}


