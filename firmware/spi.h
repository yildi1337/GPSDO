/*----------------------------------------------------------------------------------
    Description:    SPI driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef SPI_H
#define SPI_H

#include "main.h"

#define SPI_HARDWARE		0

#define SPI_DDR_MOSI		DDRB
#define SPI_PORT_MOSI		PORTB
#define SPI_PIN_MOSI		5

#define SPI_DDR_MISO		DDRB
#define SPI_PORT_MISO		PORTB
#define SPI_PIN_MISO		6

#define SPI_DDR_CLK			DDRB
#define SPI_PORT_CLK		PORTB
#define SPI_PIN_CLK			7

extern void spi_init(void);
extern void spi_write(uint8_t data);
extern uint8_t spi_read(void);
extern void spi_wait_for_transmission_complete(void);

#endif