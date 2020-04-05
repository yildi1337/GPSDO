/*----------------------------------------------------------------------------------
    Description:    SPI driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

void spi_init(void)
{
	/* set MOSI pin as output */
	SPI_DDR_MOSI = SPI_DDR_MOSI | (1 << SPI_PIN_MOSI);
	
	/* set MISO pin as input */
	SPI_DDR_MISO = SPI_DDR_MISO & ~(1 << SPI_PIN_MISO);
	
	/* set SLK pin as output */
	SPI_DDR_CLK = SPI_DDR_CLK | (1 << SPI_PIN_CLK);
	
	#if SPI_HARDWARE == 1	
		/* send MSB first */
		SPCR &= ~(1 << DORD);
	
		/* master */
		SPCR |= (1 << MSTR);
	
		/* frequency = 10 MHz / 4 */
		SPCR &= ~(1 << SPR1);
		SPCR &= ~(1 << SPR0);
	
		/* enable SPI */
		SPCR |= (1 << SPE);	
	#else
		/* not needed */
	#endif
}

void spi_write(uint8_t data)
{
	#if SPI_HARDWARE == 1	
		SPDR = data;	
	#else
		for (uint8_t i = 0; i < 8; i++) {
			
			if (((data >> (7-i)) & 0x01) == 1)
				SPI_PORT_MOSI |= (1 << SPI_PIN_MOSI);
			else
				SPI_PORT_MOSI &= ~(1 << SPI_PIN_MOSI);
			
			SPI_PORT_CLK |= (1 << SPI_PIN_CLK);
			SPI_PORT_CLK &= ~(1 << SPI_PIN_CLK);
		}
	#endif
}

uint8_t spi_read(void)
{
	#if SPI_HARDWARE == 1
		return SPDR;	
	#else
		/* not implemented */
		return 0;
	#endif
}

void spi_wait_for_transmission_complete(void)
{
	#if SPI_HARDWARE == 1
		/* wait for transmission complete */
		while (!(SPSR & (1 << SPIF)));
	#else
		/* not needed */
	#endif
	
	
}

