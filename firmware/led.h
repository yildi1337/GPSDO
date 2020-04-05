/*----------------------------------------------------------------------------------
    Description:    LED driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef LED_H
#define LED_H

#include "main.h"

#define LED_PORT		PORTD
#define LED_DDR			DDRD
#define LED_1			3
#define LED_2			4
#define LED_3			5

#define LED_1_ON		LED_PORT |= (1 << LED_1)
#define LED_2_ON		LED_PORT |= (1 << LED_2)
#define LED_3_ON		LED_PORT |= (1 << LED_3)

#define LED_1_OFF		LED_PORT &= ~(1 << LED_1)
#define LED_2_OFF		LED_PORT &= ~(1 << LED_2)
#define LED_3_OFF		LED_PORT &= ~(1 << LED_3)

#define LED_1_TOGGLE	LED_PORT ^= (1 << LED_1)
#define LED_2_TOGGLE	LED_PORT ^= (1 << LED_2)
#define LED_3_TOGGLE	LED_PORT ^= (1 << LED_3)

extern void led_init(void);

#endif