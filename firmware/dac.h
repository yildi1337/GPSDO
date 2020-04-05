/*----------------------------------------------------------------------------------
    Description:    DAC (AD5541) driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef DAC_H
#define DAC_H

#include "main.h"

#define DAC_DDR_nCS			DDRB
#define DAC_PORT_nCS		PORTB
#define DAC_PIN_nCS			3

#define DAC_VREF			5
#define DAC_RESOLUTION		65536
#define DAC_VLSB			((float)(DAC_VREF/DAC_RESOLUTION))

extern void dac_init(void);
extern void dac_spi_enable(void);
extern void dac_spi_disable(void);
extern void dac_set_voltage(float voltage);
extern void dac_set_digital_value(uint16_t value);
extern void dac_write(uint16_t data);

#endif