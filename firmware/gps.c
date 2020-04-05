/*----------------------------------------------------------------------------------
    Description:    GPS (u-blox NEO-7N) driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

GPS_INTERRUPT_EDGE_t gps_interrupt_edge = GPS_INTERRUPT_EDGE_UNDEFINED;

void gps_init(void)
{
	/* set nRESET pin as output */
	GPS_DDR_nRESET |= (1 << GPS_PIN_nRESET);
	
	/* set TIMEPULSE pin as input */
	GPS_DDR_TIMEPULSE &= ~(1 << GPS_PIN_TIMEPULSE);
	
	/* set nCS pin as output */
	GPS_DDR_nCS |= (1 << DAC_PIN_nCS);
	
	/* enable GPS */
	gps_enable();
}

void gps_enable(void)
{
	GPS_PORT_nRESET = GPS_PORT_nRESET | (1 << GPS_PIN_nRESET);
}

void gps_disable(void)
{
	GPS_PORT_nRESET = GPS_PORT_nRESET & ~(1 << GPS_PIN_nRESET);
}

void gps_timepulse_interrupt_enable(GPS_INTERRUPT_EDGE_t edge)
{
	if (edge == GPS_INTERRUPT_EDGE_RISING) {
		
		/* trigger rising edge */
		EICRA |= (1 << ISC00);
		EICRA |= (1 << ISC01);
		gps_interrupt_edge = GPS_INTERRUPT_EDGE_RISING;
	}
	else if (edge == GPS_INTERRUPT_EDGE_FALLING) {
		
		/* trigger falling edge */
		EICRA &= ~(1 << ISC00);
		EICRA |= (1 << ISC01);
		gps_interrupt_edge = GPS_INTERRUPT_EDGE_FALLING;
	}
	
	/* enable external interrupt INT0 */	
	EIMSK |= (1 << INT0);
	
	/* clear interrupt flag */
	EIFR |= (1 << INT0);
}

void gps_timepulse_interrupt_disable(void)
{
	/* disable external interrupt INT0 */
	EIMSK &= ~(1 << INT0);
	gps_interrupt_edge = GPS_INTERRUPT_EDGE_UNDEFINED;
}

void gps_spi_enable(void)
{
	GPS_PORT_nCS &= ~(1 << GPS_PIN_nCS);
}

void gps_spi_disable(void)
{
	GPS_PORT_nCS |= (1 << GPS_PIN_nCS);
}

