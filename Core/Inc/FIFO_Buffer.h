
#ifndef INC_FIFO_BUFFER_H_
#define INC_FIFO_BUFFER_H_

#include "DataHandles.h"

#define BUFFER_SIZE			10

/*
 *********************************************************
 * FIFO Buffer Data Structure Definition
 *********************************************************
 */

typedef struct
{
	char buffer[BUFFER_SIZE];
	int front, rear;
	int size;
}FIFO_Buffer;


/*
 *********************************************************
 * Function Declarations
 *********************************************************
 */

void ClearBuffer(FIFO_Buffer *Buffer);
bool Push(FIFO_Buffer *Buffer, char character);
char Pop(FIFO_Buffer *Buffer);

#endif /* INC_FIFO_BUFFER_H_ */
