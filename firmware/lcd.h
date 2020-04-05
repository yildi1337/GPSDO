/*----------------------------------------------------------------------------------
    Description:    LCD driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#ifndef LCD_H
#define LCD_H

#include "main.h"

#define LCD_DDR_RS		DDRA
#define LCD_PORT_RS		PORTA
#define LCD_PIN_RS		5

#define LCD_DDR_RW		DDRA
#define LCD_PORT_RW		PORTA
#define LCD_PIN_RW		6

#define LCD_DDR_E		DDRA
#define LCD_PORT_E		PORTA
#define LCD_PIN_E		7

#define LCD_DDR_DB		DDRC
#define LCD_PORT_DB		PORTC

#define LCD_BOOTUP_MS			15
#define LCD_ENABLE_US			20
#define LCD_WRITEDATA_US		46
#define LCD_COMMAND_US			42

#define LCD_SOFT_RESET_MS1		5
#define LCD_SOFT_RESET_MS2		1
#define LCD_SOFT_RESET_MS3		1
#define LCD_SET_4BITMODE_MS		5
#define LCD_SET_8BITMODE_MS		5

#define LCD_CLEAR_DISPLAY_MS	2
#define LCD_CURSOR_HOME_MS		2

#define LCD_DDADR_LINE1			0x00
#define LCD_DDADR_LINE2			0x40

#define LCD_CLEAR_DISPLAY		0x01
#define LCD_CURSOR_HOME			0x02
#define LCD_SET_ENTRY			0x04

#define LCD_ENTRY_DECREASE		0x00
#define LCD_ENTRY_INCREASE		0x02
#define LCD_ENTRY_NOSHIFT		0x00
#define LCD_ENTRY_SHIFT			0x01

#define LCD_SET_DISPLAY			0x08

#define LCD_DISPLAY_OFF			0x00
#define LCD_DISPLAY_ON			0x04
#define LCD_CURSOR_OFF			0x00
#define LCD_CURSOR_ON			0x02
#define LCD_BLINKING_OFF		0x00
#define LCD_BLINKING_ON			0x01

#define LCD_SET_SHIFT			0x10

#define LCD_CURSOR_MOVE			0x00
#define LCD_DISPLAY_SHIFT		0x08
#define LCD_SHIFT_LEFT			0x00
#define LCD_SHIFT_RIGHT			0x04

#define LCD_SET_FUNCTION		0x20

#define LCD_FUNCTION_4BIT		0x00
#define LCD_FUNCTION_8BIT		0x10
#define LCD_FUNCTION_1LINE		0x00
#define LCD_FUNCTION_2LINE		0x08
#define LCD_FUNCTION_5X7		0x00
#define LCD_FUNCTION_5X10		0x04

#define LCD_SOFT_RESET			0x30

#define LCD_SET_CGADR			0x40

#define LCD_GC_CHAR0			0
#define LCD_GC_CHAR1			1
#define LCD_GC_CHAR2			2
#define LCD_GC_CHAR3			3
#define LCD_GC_CHAR4			4
#define LCD_GC_CHAR5			5
#define LCD_GC_CHAR6			6
#define LCD_GC_CHAR7			7

#define LCD_SET_DDADR			0x80

extern void lcd_init(void);
extern void lcd_clear(void);
extern void lcd_home(void);
extern void lcd_setcursor(uint8_t x, uint8_t y);
extern void lcd_data(uint8_t data);
extern void lcd_string(const char *data);
extern void lcd_int(uint16_t data);
extern void lcd_float(float data);
extern void lcd_float64_freq_MHz(float64_t freq, uint8_t number_of_chars);
extern void lcd_command(uint8_t command);
extern void lcd_string_append(char str[], const char insert[], int pos);

#endif