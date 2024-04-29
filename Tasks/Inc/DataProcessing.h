#ifndef INC_DATAPROCESSING_H_
#define INC_DATAPROCESSING_H_

#include "DataHandles.h"

#define FIR_FILTER_ORDER		16
#define IIR_FILTER_ORDER		2


/*
 * **********************************************
 * FIR Filter Coefficients - Designed in MATLAB
 * **********************************************
 */

extern const float FIR_FILTER_COEFFICIENTS[FIR_FILTER_ORDER + 1];

/*
 * **********************************************
 * IIR Filter Coefficients - Deprecated
 * **********************************************
 *
extern const float NUMERATOR_CASCADE1_COEFFICIENTS[IIR_FILTER_ORDER + 1];
extern const float DENOMINATOR_CASCADE1_COEFFICIENTS[IIR_FILTER_ORDER];
extern const float GAIN_CASCADE1;


extern const float NUMERATOR_CASCADE2_COEFFICIENTS[IIR_FILTER_ORDER + 1];
extern const float DENOMINATOR_CASCADE2_COEFFICIENTS[IIR_FILTER_ORDER];
extern const float GAIN_CASCADE2;

extern const float NUMERATOR_CASCADE3_COEFFICIENTS[IIR_FILTER_ORDER + 1];
extern const float DENOMINATOR_CASCADE3_COEFFICIENTS[IIR_FILTER_ORDER];
extern const float GAIN_CASCADE3;*/

/*
 * **********************************************
 * FIR Low Pass Filter Data Structure
 * **********************************************
 */

typedef struct
{
	//Initialize 2 FIFO buffers to hold the data
	float moving_avg_buffer[FIR_FILTER_ORDER + 1];
	//Define the head for the FIFO Buffers
	uint8_t input_front;

	float output;

}FIR_LowPass_Filter;

/*
 * **********************************************
 * IIR Low Pass Filter Data Structure
 * **********************************************
 */

typedef struct
{
	float buffer[2];
	float numerator_coefficients[3];
	float denominator_coefficients[2];
	float gain;

}IIR_LowPass_Filter;

/*
 * **********************************************
 * Function Declarations
 * **********************************************
 */

void DataProcessing();


#endif /* INC_DATAPROCESSING_H_ */
