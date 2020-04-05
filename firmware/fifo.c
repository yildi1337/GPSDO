/*----------------------------------------------------------------------------------
    Description:    FIFO ringbuffer with averaging.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

float64_t fifo_data[FIFO_MAX_SIZE];
uint16_t fifo_index;
uint16_t fifo_current_size;

void fifo_init(void)
{
	/* initialize fifo */
	for (uint16_t i = 0; i < FIFO_MAX_SIZE; i++) {
		fifo_data[i] = 0;
	}

	/* point on first element */
	fifo_index = 0;

	/* fifo still empty */
	fifo_current_size = 0;
}

void fifo_add(float64_t data)
{
	/* add data at current position */
	fifo_data[fifo_index] = data;

	/* point on next position */
	fifo_index++;

	/* point to the start if the end is reached */
	if (fifo_index == FIFO_MAX_SIZE)
		fifo_index = 0;

	/* increase current fifo size */
	if (fifo_current_size < FIFO_MAX_SIZE)
		fifo_current_size++;
}

float64_t fifo_get_mean(void)
{
	float64_t mean = fp64_sd(0.0);
	for (uint16_t i = 0; i < fifo_current_size; i++) {
		mean = fp64_add(mean, fifo_data[i]);
	}
	return fp64_div(mean, fp64_sd((float)fifo_current_size));
}
