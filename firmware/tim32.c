/*----------------------------------------------------------------------------------
    Description:    32-bit timer.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

/* software counter */
uint32_t tim32_ticks = 0;

void tim32_init(void)
{
	/* reset timer */
	TCCR1A = 0;
	TCCR1B = 0;
	
	/* clear ticks */
	tim32_clear();
	
	/* overflow interrupt enable */
	TIMSK1 |= (1 << TOIE1);
}

void tim32_start(void)
{
	/* running with no prescaler (10 MHz) */
	TCCR1B = 0x01;
}

void tim32_stop(void)
{
	/* no clock source */
	TCCR1B = 0;
}

void tim32_clear(void)
{
	/* clear hardware and software counter */
	TCNT1 = 0;
	tim32_ticks = 0;
}

uint32_t tim32_get_ticks(void)
{
	/* return sum of hardware and software counter */
	return TCNT1 + tim32_ticks;
}

