/*----------------------------------------------------------------------------------
    Description:    ADC (internal) driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

void adc_init(void)
{
	/* AVCC with external capacitor at AREF pin */
	ADMUX &= ~(1 << REFS1);
	ADMUX |= (1 << REFS0);

	/* clock prescaler: 128 -> 10 MHz / 128 = 78.125 kHz */
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_get_value(uint8_t channel)
{
	if (channel == ADC_CHANNEL_OCXO_CURRENT) {
		ADMUX = 0b01001101;		/* differential input: ADC3-ADC2 */
	}
	else if (channel == ADC_CHANNEL_OCXO_VCTRL) {
		ADMUX = 0b01000001;		/* single ended input: ADC1 */
	}

	/* enable ADC */
	ADCSRA |= (1 << ADEN);

	/* start conversion and wait until conversion is finished */
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));

	/* read ADC value */
	uint16_t adc_value = 0;
	adc_value = ADCL;
	adc_value += (ADCH << 8);

	/* disable ADC */
	ADCSRA &= ~(1 << ADEN);

	/* return read value */
	return adc_value;
}

