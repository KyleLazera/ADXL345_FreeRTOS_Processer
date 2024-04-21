#ifndef SRC_PROJECT_DRIVERS_INC_PROGRAMINIT_H_
#define SRC_PROJECT_DRIVERS_INC_PROGRAMINIT_H_

/*
 ******************************************
 * Task Inclusions
 ******************************************
 */

#include "ReadSPIData.h"
#include "DataProcessing.h"
#include "UART_Gatekeeper.h"
#include "CLI_Interface.h"
#include "PulseWidthMod_Output.h"

/*
 ****************************************************
 *Pre-Processor Directives
 ****************************************************
 */

/**** Stack Size ****/
#define STACK_SIZE_100					100
#define STACK_SIZE_200					200
#define STACK_SIZE_500					500
#define STACK_SIZE_1000					1000

/**** Priority ****/
#define PRIORITY_1						1
#define PRIORITY_2						2
#define PRIORITY_3						3
#define PRIORITY_4						4

/*
 ****************************************************
 *Function Declarations
 ****************************************************
 */
uint8_t ProgramInit();


#endif /* SRC_PROJECT_DRIVERS_INC_PROGRAMINIT_H_ */
