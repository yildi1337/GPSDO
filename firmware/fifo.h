/*----------------------------------------------------------------------------------
    Description:    FIFO ringbuffer with averaging.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef FIFO_H
#define FIFO_H

#include "main.h"

#define FIFO_MAX_SIZE		(MAIN_AVERAGING_TIME_IN_MINUTES*60/MAIN_GATE_TIME_IN_SECONDS)

extern void fifo_init(void);
extern void fifo_add(float64_t data);
extern float64_t fifo_get_mean(void);

#endif