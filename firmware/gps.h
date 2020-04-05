/*----------------------------------------------------------------------------------
    Description:    GPS (u-blox NEO-7N) driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef GPS_H
#define GPS_H

#include "main.h"

#define GPS_DDR_nRESET		DDRB
#define GPS_PORT_nRESET		PORTB
#define GPS_PIN_nRESET		0

#define GPS_DDR_TIMEPULSE	DDRD
#define GPS_PORT_TIMEPULSE	PORTD
#define GPS_PIN_TIMEPULSE	2

#define GPS_DDR_nCS			DDRB
#define GPS_PORT_nCS		PORTB
#define GPS_PIN_nCS			4

typedef enum
{
	GPS_INTERRUPT_EDGE_UNDEFINED,
	GPS_INTERRUPT_EDGE_RISING,
	GPS_INTERRUPT_EDGE_FALLING
} GPS_INTERRUPT_EDGE_t;
extern GPS_INTERRUPT_EDGE_t gps_interrupt_edge;

extern void gps_init(void);
extern void gps_enable(void);
extern void gps_disable(void);
extern void gps_timepulse_interrupt_enable(GPS_INTERRUPT_EDGE_t edge);
extern void gps_timepulse_interrupt_disable(void);
extern void gps_spi_enable(void);
extern void gps_spi_disable(void);

#endif