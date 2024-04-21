#include "DataProcessing.h"


/*
 * ***************************************************************************
 * IIR Low Pass Filter Functions
 * ***************************************************************************
 */

/*
 * @Brief	This function is used to initialize a singular cascade in a higher order IIR filter. This function initializes the
 * 			coefficients and the gain.
 *
 * @Note	Implementing higher order IIR filters linearly (similar to the way the FIR filter was implemented) can lead to exponential
 * 			oscillations of the output. To implement the IIR filter, it is considered better practice to use a system of second order polynomials/
 * 			product of bi-quads.
 *
 * @Note	To see design of filter see README file
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
		//Initialize Coefficients for numerator
		filter->numerator_coefficients[i] = num_coeff[i];
	}

	//Initialize gain
	filter->gain = gain;
}

/*
 * @Brief	Algorithm to implement the IIR filter using product of Biquads
 *
 * @Note	This filter is based offf an elliptic lowpass filter - designed in MATLAB.
 *
 * @Note	To see how these equations were derived see README
 */
static void CascadeIIR(IIR_LowPass_Filter *filter, AccelerometerData *input)
{
	//Algorithm to calculate the intermediate value: w(n) = x(n) - a0*w(n-1) - a1*w(n-2)
	float intermediate = (input->value) - (filter->buffer[0] * filter->denominator_coefficients[0]) - (filter->buffer[1] * filter->denominator_coefficients[1]);
	//Algorithm to calculate the final output value: y(n) = b1*w(n) + b2*w(n-1) + b3*w(n-2)
	float output = (intermediate * filter->numerator_coefficients[0]) + (filter->buffer[0] * filter->numerator_coefficients[1]) + (filter->buffer[1] * filter->numerator_coefficients[2]);
	//Multiply the output by the filter gain
	output *= filter->gain;
	(input->value) = output;

	//Shift/delay buffer values
	filter->buffer[1] = filter->buffer[0];
	filter->buffer[0] = intermediate;

}

/*
 * ***************************************************************************
 * FIR Low Pass Filter Functions
 * ***************************************************************************
 */

/*
 * @Brief	Used to initialize the FIR filter by setting default values to 0.
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
	//Set the initial output to 0
	filter->output = 0.0f;

}


/*
 * @Brief	Algorithm used to implement the FIR low-pass filter.
 *
 * @Note	This filter (unlike the IIR) was implemented linearly based off the convolution sum formula.
 *
 * @Note	This filter is based off a low pass FIR filter with a Hanning window applied.
 */
static void FIRFilterComputation(FIR_LowPass_Filter *filter, AccelerometerData *input)
{
	uint8_t indexCounter;

	//Store the current input in the FIFO
	filter->moving_avg_buffer[filter->input_front] = input->value;

	//Increment the head of the FIFO and ensure it wraps around forming a circular buffer
	filter->input_front = (filter->input_front + 1) % (FIR_FILTER_ORDER + 1);

	indexCounter = filter->input_front;
	filter->output = 0.0f;

	//Convolution of input values and coefficients
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

	input->value = filter->output;
}

void DataProcessing(void *pvParameters)
{
	AccelerometerData rec_data;
	FIR_LowPass_Filter x_lowpass, y_lowpass, z_lowpass;
	float input = 0.0, output = 0;

	/*IIR_LowPass_Filter cascade1, cascade2, cascade3;
	InitCascade(&cascade1, NUMERATOR_CASCADE1_COEFFICIENTS, DENOMINATOR_CASCADE1_COEFFICIENTS, IIR_FILTER_ORDER, GAIN_CASCADE1);
	InitCascade(&cascade2, NUMERATOR_CASCADE2_COEFFICIENTS, DENOMINATOR_CASCADE2_COEFFICIENTS, IIR_FILTER_ORDER, GAIN_CASCADE2);
	InitCascade(&cascade3, NUMERATOR_CASCADE3_COEFFICIENTS, DENOMINATOR_CASCADE3_COEFFICIENTS, IIR_FILTER_ORDER, GAIN_CASCADE3);*/

	InitFIRFilter(&x_lowpass);
	InitFIRFilter(&y_lowpass);
	InitFIRFilter(&z_lowpass);
	TickType_t _10ms = pdMS_TO_TICKS(10);

	while(1)
	{
		filterTask++;

		xQueueReceive(adxl_data_queue, &rec_data, 0);			//Read accelerometer data from FreeRTOS queue

		switch(rec_data.axis)
		{
			case x_axis:
				input = rec_data.value;
				FIRFilterComputation(&x_lowpass, &rec_data);
				break;

			case y_axis:
				FIRFilterComputation(&y_lowpass, &rec_data);
				break;

			case z_axis:
				FIRFilterComputation(&z_lowpass, &rec_data);
				break;
		}

		xQueueSend(filtered_data_queue, &rec_data, _10ms);
	}
}



