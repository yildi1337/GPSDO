/*----------------------------------------------------------------------------------
    Description:    32-bit timer.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef TIM32_H
#define TIM32_H

#include "main.h"

/* software counter */
extern uint32_t tim32_ticks;

extern void tim32_init(void);
extern void tim32_start(void);
extern void tim32_stop(void);
extern void tim32_clear(void);
extern uint32_t tim32_get_ticks(void);

#endif