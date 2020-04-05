/*----------------------------------------------------------------------------------
    Description:    ADC (internal) driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef ADC_H
#define ADC_H

#include "main.h"

#define ADC_CHANNEL_OCXO_CURRENT				0
#define ADC_CHANNEL_OCXO_VCTRL					1

#define ADC_DIFF_GAIN							10
#define ADC_RESOLUTION							1024
#define ADC_VREF								5
#define ADC_VADC2								2.481
#define ADC_VLSB								ADC_VREF/1024
#define ADC_VALUE_TO_OCXO_CURRENT_SE(x)			((float)(x-(ADC_RESOLUTION/2))) * ADC_VLSB / ACS712_FACTOR;
#define ADC_VALUE_TO_OCXO_CURRENT_DIFF(x)		(((((float)(x)) / (ADC_DIFF_GAIN * (ADC_RESOLUTION/2) / ADC_VREF)) + ADC_VADC2) - ACS712_VOFFSET) / ACS712_FACTOR;
#define ADC_VALUE_TO_OCXO_VCTRL_SE(x)			((float)(x)) * ADC_VLSB;

extern void adc_init(void);
extern uint16_t adc_get_value(uint8_t channel);

#endif