/*----------------------------------------------------------------------------------
    Description:    Generic includes and defines.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef _MAIN_H
#define _MAIN_H
 
#define F_CPU				10000000L

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <fp64lib.h>
#include "led.h"
#include "adc.h"
#include "dac.h"
#include "gps.h"
#include "lcd.h"
#include "spi.h"
#include "tim32.h"
#include "fifo.h"

#define MAIN_GATE_TIME_IN_SECONDS			60
#define MAIN_AVERAGING_TIME_IN_MINUTES		10		

#define ACS712_FACTOR						0.185
#define ACS712_VOFFSET						2.513

extern void init(void);
extern int main(void);

#endif
