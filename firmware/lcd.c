/*----------------------------------------------------------------------------------
    Description:    LCD driver.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

static void lcd_enable(void)
{
	LCD_PORT_E |= (1 << LCD_PIN_E);
	_delay_us(LCD_ENABLE_US);
	LCD_PORT_E &= ~(1 << LCD_PIN_E);
}

void lcd_init(void)
{
	/* configure pins */	
	LCD_DDR_RS |= (1 << LCD_PIN_RS);
	LCD_DDR_RW |= (1 << LCD_PIN_RW);
	LCD_DDR_E |= (1 << LCD_PIN_E);
	LCD_DDR_DB = 0xff;
	
	LCD_PORT_RS &= ~(1 << LCD_PIN_RS);
	LCD_PORT_RW &= ~(1 << LCD_PIN_RW);
	LCD_PORT_E &= ~(1 << LCD_PIN_E);
	LCD_PORT_DB = 0x00;	 
	
	/* wait for bootup */
	_delay_ms(LCD_BOOTUP_MS);
	
	/* software reset */
	lcd_command(LCD_SOFT_RESET);
	_delay_ms(LCD_SOFT_RESET_MS1);	
	lcd_enable();
	_delay_ms(LCD_SOFT_RESET_MS2);	
	lcd_enable();
	_delay_ms(LCD_SOFT_RESET_MS3);
	
	/* configure display */
	lcd_command(LCD_SET_FUNCTION | LCD_FUNCTION_8BIT);
	_delay_ms(LCD_SET_8BITMODE_MS);	
	lcd_command(LCD_SET_FUNCTION | LCD_FUNCTION_8BIT | LCD_FUNCTION_2LINE | LCD_FUNCTION_5X7);	
	lcd_command(LCD_SET_DISPLAY | LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINKING_OFF);
	lcd_command(LCD_SET_ENTRY | LCD_ENTRY_INCREASE | LCD_ENTRY_NOSHIFT);	
	lcd_clear();
}

void lcd_data(uint8_t data)
{
	LCD_PORT_RS |= (1 << LCD_PIN_RS);	
	LCD_PORT_DB = data;	
	_delay_us(LCD_WRITEDATA_US);
	lcd_enable();	
}

void lcd_command(uint8_t command)
{
	LCD_PORT_RS &= ~(1 << LCD_PIN_RS);
	LCD_PORT_DB = command;
	_delay_us(LCD_WRITEDATA_US);
	lcd_enable();
}

void lcd_clear(void)
{
	lcd_command(LCD_CLEAR_DISPLAY);
	_delay_ms(LCD_CLEAR_DISPLAY_MS);
}

void lcd_home(void)
{
	lcd_command(LCD_CURSOR_HOME);
	_delay_ms(LCD_CURSOR_HOME_MS);
}

void lcd_setcursor(uint8_t x, uint8_t y)
{
	uint8_t data;
	
	switch (y)
	{
		case 1:
			data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
			break;
		
		case 2:
			data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
			break;
		
		default:
			return;
	}
	
	lcd_command(data);
}

void lcd_int(uint16_t data)
{
	char str[20];
	sprintf(str, "%d", data);
	lcd_string(str);
}

void lcd_float(float data)
{
	char str[20];
	sprintf(str, "%.2f", data);
	lcd_string(str);
}

void lcd_float64_freq_MHz(float64_t freq, uint8_t number_of_chars)
{
	char *fp64_string = fp64_to_string(fp64_div(freq, fp64_sd((float)1e6)), number_of_chars, 5);
	char buffer_freq[20];
	
	strcpy(buffer_freq, fp64_string);
	
	if (buffer_freq[0] == '9' && buffer_freq[1] == '.')
		lcd_string_append(buffer_freq, " ", 0);
	
	if (buffer_freq[2] != '.')
		lcd_string_append(buffer_freq, ".", 2);
	
	uint8_t buffer_freq_len = strlen(buffer_freq);
	for (uint8_t i = 0; i < number_of_chars-buffer_freq_len; i++)
		lcd_string_append(buffer_freq, "0", buffer_freq_len+i);
	
	lcd_string(buffer_freq);
	lcd_string(" MHz");
}

void lcd_string(const char *data)
{
	while(*data != '\0')
		lcd_data(*data++);
}

void lcd_string_append(char str[], const char insert[], int pos)
{
	char buf[40] = { 0 };
	
	strncpy(buf, str, pos);
	int len = strlen(buf);
	strcpy(buf+len, insert);
	len += strlen(insert);
	strcpy(buf+len, str+pos);
	strcpy(str, buf);
}