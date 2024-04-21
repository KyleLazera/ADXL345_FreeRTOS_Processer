#ifndef INC_DATAPROCESSING_H_
#define INC_DATAPROCESSING_H_

#include "DataHandles.h"

#define FIR_FILTER_ORDER		16
#define IIR_FILTER_ORDER		2

/*
 * **********************************************
 * IIR Filter Coefficients
 * **********************************************
 */
static float NUMERATOR_CASCADE1_COEFFICIENTS[IIR_FILTER_ORDER + 1] = {1.0f, 1.525505452575259379699446071754209697247f, 1.0f};
static float DENOMINATOR_CASCADE1_COEFFICIENTS[IIR_FILTER_ORDER] = {-0.823830112694799665540301703003933653235f,  0.62050953364421035374220991798210889101f};
static float GAIN_CASCADE1 = 0.645660817653338492405623583181295543909f;


static float NUMERATOR_CASCADE2_COEFFICIENTS[IIR_FILTER_ORDER + 1] = {1.0f, 1.926899025203367532554921126575209200382f, 1.0f};
static float DENOMINATOR_CASCADE2_COEFFICIENTS[IIR_FILTER_ORDER] = {-1.178414131460015612518077432468999177217f,  0.418440143742314807351334593477076850832f};
static float GAIN_CASCADE2 = 1.558318741266783380439164830022491514683f;

static float NUMERATOR_CASCADE3_COEFFICIENTS[IIR_FILTER_ORDER + 1] = {1.0f, 1.217004950031076448979661108751315623522f, 1.0f};
static float DENOMINATOR_CASCADE3_COEFFICIENTS[IIR_FILTER_ORDER] = {-0.554734277598179392754218497429974377155f,  0.86945391770266144959578014095313847065f};
static float GAIN_CASCADE3 = 0.005327107737438318071920839713584427955f;

/*
 * **********************************************
 * FIR Filter Coefficients
 * **********************************************
 */

static float FIR_FILTER_COEFFICIENTS[FIR_FILTER_ORDER + 1] = { 0.0f, 0.0036676f, 0.0153805f, 0.0347811f, 0.0595925f, 0.0859952f,
															0.1094142f, 0.1255314f, 0.1312742f, 0.1255314f, 0.1094142f, 0.0859952f,
															0.0595925f, 0.0347811f, 0.0153805f, 0.0036676f, 0.0f};

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
