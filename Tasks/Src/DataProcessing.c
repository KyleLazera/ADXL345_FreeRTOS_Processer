#include "DataProcessing.h"


/*
 * ***************************************************************************
 * IIR Low Pass Filter Functions
 * ***************************************************************************
 */

/*
 * @Note: IIR Filter not used as FIR filter better suited this scenario. Due to needing to filter data from the x, y and z axis, and IIR filter
 * would require 3 different filters each made up of 3 cascades as they utilize previous outputs of data. Therefore, in terms of implementation, it made more
 * sense to utilize the FIR filter.
 */

/*
 * @Brief	This function is used to initialize a singular cascade in a higher order IIR filter. This function initializes the
 * 			coefficients and the gain.
 *
 * @Note	Implementing higher order IIR filters linearly (similar to the way the FIR filter was implemented) can lead to exponential
 * 			oscillations of the output. To implement the IIR filter, I used a system of second order polynomials (bi-quads) in a cascade.
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

/*
 * @Brief	Function used to create data processing thread
 */
void DataProcessing()
{
	AccelerometerData rec_data;
	FIR_LowPass_Filter x_lowpass, y_lowpass, z_lowpass;

	InitFIRFilter(&x_lowpass);
	InitFIRFilter(&y_lowpass);
	InitFIRFilter(&z_lowpass);

	while(1)
	{
		filterTask++;

		xQueueReceive(adxl_data_queue, &rec_data, 0);			//Read accelerometer data from FreeRTOS queue

		switch(rec_data.axis)
		{
			case x_axis:
				FIRFilterComputation(&x_lowpass, &rec_data);
				break;

			case y_axis:
				FIRFilterComputation(&y_lowpass, &rec_data);
				break;

			case z_axis:
				FIRFilterComputation(&z_lowpass, &rec_data);
				break;

			case no_axis:
				break;
		}


		xQueueSend(filtered_data_queue, &rec_data, _10ms);
	}
}



