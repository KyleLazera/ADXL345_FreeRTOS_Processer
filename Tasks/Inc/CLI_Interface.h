#ifndef INC_CLI_INTERFACE_H_
#define INC_CLI_INTERFACE_H_

#include "DataHandles.h"
#include "FIFO_Buffer.h"
#include  "string.h"

/*
 ********************************************************
 * Pre-Defined Command Line Messages
 ********************************************************
 */
extern const char x_axis_[];
extern const char y_axis_[];
extern const char z_axis_[];

/*
 **********************************************************
 * Function Declarations
 **********************************************************
 */

void CommandLineRead();

#endif /* INC_CLI_INTERFACE_H_ */
