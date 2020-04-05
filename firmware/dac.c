/*----------------------------------------------------------------------------------
    Description:    DAC (AD5541) driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

void dac_init(void)
{
	/* set nCS pin as output */
	DAC_DDR_nCS |= (1 << DAC_PIN_nCS);
	
	/* disable SPI communication */
	dac_spi_disable();
}

void dac_spi_enable(void)
{
	DAC_PORT_nCS &= ~(1 << DAC_PIN_nCS);
}

void dac_spi_disable(void)
{
	DAC_PORT_nCS |= (1 << DAC_PIN_nCS);
}

void dac_set_voltage(float voltage)
{
	uint16_t D = (uint16_t)(voltage * ((float)DAC_RESOLUTION) / ((float)DAC_VREF));
	dac_write(D);
}

void dac_set_digital_value(uint16_t value)
{
	dac_write(value);
}

void dac_write(uint16_t data)
{
	dac_spi_enable();
	spi_write((data >> 8) & 0xff);
	spi_wait_for_transmission_complete();
	spi_write(data & 0x00ff);
	spi_wait_for_transmission_complete();
	dac_spi_disable();
}

