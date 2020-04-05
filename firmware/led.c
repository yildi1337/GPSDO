/*----------------------------------------------------------------------------------
    Description:    LED driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

void led_init(void)
{
	/* set LED pins as outputs */
	LED_DDR |= (1 << LED_1);
	LED_DDR |= (1 << LED_2);
	LED_DDR |= (1 << LED_3);

	/* switch of all LEDs */
	LED_1_OFF;
	LED_2_OFF;
	LED_3_OFF;
}
