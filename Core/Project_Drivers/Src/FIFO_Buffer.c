#include "FIFO_Buffer.h"

/*
 * @Brief	Initialize or clear all the buffer values
 */
void ClearBuffer(FIFO_Buffer *Buffer)
{
	int index;

	for(index = 0; index < BUFFER_SIZE - 1; index++)
	{
		Buffer->buffer[index] = 0;
	}
	Buffer->front = 0;
	Buffer->rear = 0;
	Buffer->size = 0;
}

/*
 * @Brief Push characters into the FIFO buffer
 */
bool Push(FIFO_Buffer *Buffer, char character)
{
	//If FIFo is full return false
	if(Buffer->size == BUFFER_SIZE)
		return false;

	//Push the char into FIFO and increment rear
	Buffer->buffer[Buffer->rear] = character;
	Buffer->rear = (Buffer->rear + 1) % BUFFER_SIZE;
	Buffer->size++;
	return true;
}

/*
 * @Brief	Pop characters from the FIFO Buffer
 */
char Pop(FIFO_Buffer *Buffer)
{
	char value_to_return;

	//Check if the FIFO is empty
	if(Buffer->size == 0)
		return -1;

	value_to_return = Buffer->buffer[Buffer->front];
	//If the back of the queue has reached the front of the queue. ie All chars are read
	if(Buffer->front == Buffer->rear)
	{
		Buffer->front = Buffer->rear = 0;
	}
	else
	{
		//Increment the front buffer
		Buffer->front = (Buffer->front + 1) % BUFFER_SIZE;
	}

	Buffer->size--;
	return value_to_return;
}

