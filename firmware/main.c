/*----------------------------------------------------------------------------------
    Description:    Main program of the 10 MHz GPS Disciplined Oscillator.
    Date:           04/05/2020
    Author:         Phillip Durdaut
----------------------------------------------------------------------------------*/

#include "main.h"

/* the time the 32-bit counter is running */
#define MAIN_GPS_PPS_AVERAGE_IN_SECONDS		MAIN_GATE_TIME_IN_SECONDS

/* the number of chars of the displayed frequency */
#define MAIN_LCD_FREQ_NUMBER_OF_CHARS		11

/* time in ms to display status messages */
#define MAIN_LCD_TIME_STATUS_MESSAGES_MS	2500

/* time after which the display is updated */
#define MAIN_LCD_UPDATE_TIME_MS				100

/* DAC value */
uint16_t main_dac_vctrl_digital_value = (uint16_t)(DAC_RESOLUTION/2);

/* flag whether GPS is available */
uint8_t main_gps_available = 0;

/* counter for the GPS PPS pulses */
uint8_t main_gps_edge_counter = 0;

/* counter for LCD blinking */
uint8_t main_lcd_blink_counter = 0;

/* prototypes of additional functions */
void init(void);
void update_lcd_first_line(void);
int8_t compare_frequencies(float64_t measured, float64_t reference);

/* main program */
int main(void)
{
	/* initialize all modules */
	init();

	/* welcome message */
	lcd_clear();
	lcd_setcursor(0,1);
	lcd_string("      Muin      ");
	_delay_ms(MAIN_LCD_TIME_STATUS_MESSAGES_MS);

	/* OCXO heating */
	lcd_clear();
	while (1)
	{
		_delay_ms(MAIN_LCD_UPDATE_TIME_MS);

		/* get ADC value and convert value to current */
		uint16_t adc_value = adc_get_value(ADC_CHANNEL_OCXO_CURRENT);
		float current = ADC_VALUE_TO_OCXO_CURRENT_DIFF(adc_value);

		/* display current current in second line */
		lcd_setcursor(0,2);
		lcd_string("at ");
		lcd_setcursor(3,2);
		lcd_float(current);
		lcd_string(" A ...");

		if (current > 0.4) {
			LED_1_TOGGLE;
			lcd_setcursor(0,1);
			lcd_string("OCXO heating    ");
		}
		else {
			LED_1_ON;
			lcd_setcursor(0,1);
			lcd_string("OCXO stable     ");
			_delay_ms(MAIN_LCD_TIME_STATUS_MESSAGES_MS);
			break;
		}
	}

	/* OCXO stable, waiting for GPS */
	lcd_clear();
	while(1)
	{
		_delay_ms(MAIN_LCD_UPDATE_TIME_MS);

		/* update OCXO current and control voltage in first line of LCD */
		update_lcd_first_line();

		/* GPS not yet available */
		if (!main_gps_available) {
			lcd_setcursor(0,2);
			lcd_string("Awaiting GPS ...");
		}
		else {
			lcd_setcursor(0,2);
			lcd_string("GPS available   ");
			_delay_ms(MAIN_LCD_TIME_STATUS_MESSAGES_MS);
			break;
		}
	}

	/* OCXO stable and GPS available */
	fifo_init();
	lcd_clear();
	while(1)
	{
		_delay_ms(MAIN_LCD_UPDATE_TIME_MS);

		/* update OCXO current and control voltage in first line of LCD */
		update_lcd_first_line();

		/* (average) clocks per second / per GPS pulse */
		lcd_setcursor(0,2);
		lcd_string("                ");

		float64_t ticks_average = fifo_get_mean();
		if (!fp64_isnan(ticks_average)) {

			/* display current frequency in the display's second line */
			lcd_setcursor(0,2);
			lcd_float64_freq_MHz(ticks_average, MAIN_LCD_FREQ_NUMBER_OF_CHARS);

			/* compare measured frequency to ideal frequency of 10 MHz */
			int8_t comp = compare_frequencies(ticks_average, fp64_sd((float)F_CPU));

			/* adjust OCXO control voltage */
			if (comp == -1) {
				if (main_dac_vctrl_digital_value < (DAC_RESOLUTION-1))
					main_dac_vctrl_digital_value++;
				dac_set_digital_value(main_dac_vctrl_digital_value);

				lcd_setcursor(8,1);
				main_lcd_blink_counter++;
				if (main_lcd_blink_counter < 4)
					lcd_string("+");
				if (main_lcd_blink_counter == 10)
					main_lcd_blink_counter = 0;
				LED_3_OFF;
			}
			else if (comp == 1) {
				if (main_dac_vctrl_digital_value > 0)
					main_dac_vctrl_digital_value--;
				dac_set_digital_value(main_dac_vctrl_digital_value);

				lcd_setcursor(8,1);
				main_lcd_blink_counter++;
				if (main_lcd_blink_counter < 4)
					lcd_string("-");
				if (main_lcd_blink_counter == 10)
					main_lcd_blink_counter = 0;
				LED_3_OFF;
			}
			else if (comp == 0) {
				LED_3_ON;
			}
		}
		else {
			lcd_setcursor(0,2);
			lcd_string("Measuring ...   ");
		}
	}
}

/* additional functions */
void init(void)
{
	/* init LEDs */
	led_init();

	/* init LCD */
	lcd_init();

	/* init SPI */
	spi_init();

	/* init ADC */
	adc_init();

	/* init GPS */
	gps_init();

	/* init DAC */
	dac_init();
	dac_set_digital_value(main_dac_vctrl_digital_value);

	/* init 32-bit counter */
	tim32_init();

	/* init FIFO with ideal clock frequency */
	fifo_init();

	/* enable TIMEPULSE interrupt */
	gps_timepulse_interrupt_enable(GPS_INTERRUPT_EDGE_RISING);

	/* enable all interrupts */
	sei();
}

void update_lcd_first_line(void)
{
	lcd_setcursor(0,1);
	lcd_string("                ");

	/* OCXO supply current */
	uint16_t adc_value_ocxo = adc_get_value(ADC_CHANNEL_OCXO_CURRENT);
	float current = ADC_VALUE_TO_OCXO_CURRENT_DIFF(adc_value_ocxo);
	if (current > 0.25 && current < 1.5) {
		lcd_setcursor(0,1);
		lcd_float(current);
		lcd_string(" A");
	}

	/* measured control voltage */
	uint16_t adc_value_vctrl = adc_get_value(ADC_CHANNEL_OCXO_VCTRL);
	float voltage = ADC_VALUE_TO_OCXO_VCTRL_SE(adc_value_vctrl);
	if (voltage > 0.0 && voltage < 5.0) {
		lcd_setcursor(10,1);
		lcd_float(voltage);
		lcd_string(" V");
	}
}

int8_t compare_frequencies(float64_t measured, float64_t reference)
{
	float64_t fp64_difference = fp64_sub(measured, reference);
	float64_t fp64_difference_uHz = fp64_mul(fp64_difference, fp64_sd((float)1e6));
	int64_t int64_difference_uHz = fp64_to_int64(fp64_difference_uHz);

	if (int64_difference_uHz < 0)
		return -1;

	if (int64_difference_uHz > 0)
		return 1;

	return 0;
}

/* interrupt service routines */
ISR(INT0_vect)
{
	/* ISR called on GPS PPS edge */
	if (gps_interrupt_edge == GPS_INTERRUPT_EDGE_RISING) {

		/* interrupt indicates that GPS is available now */
		main_gps_available = 1;

		main_gps_edge_counter++;
		if (main_gps_edge_counter == MAIN_GPS_PPS_AVERAGE_IN_SECONDS) {

			/* reset GPS PPS counter */
			main_gps_edge_counter = 0;

			/* ------------------------------------------------------------------------------------------------------------ */
			/* ------- 56 clock cycles between counter stop and start (with optimize -O1) extracted from *.lss file ------- */
			/* ------------------------------------------------------------------------------------------------------------ */

			/* stop counter */
			tim32_stop();										/* 9 cycles -> 5 before/4 after counter start */

			/* get number of ticks from 32-bit counter */
			uint32_t temp_tim32_ticks = tim32_get_ticks();		/* 27 cycles */

			/* reset 32-bit counter */
			tim32_clear();										/* 19 cycles */

			/* start counter */
			tim32_start();										/* 10 -> 6 before/4 after counter stop */

			/* ------------------------------------------------------------------------------------------------------------ */

			if (temp_tim32_ticks == 0) {
				/* ignore first (empty) value */
			}
			else {
				/* add corrected number of ticks to the fifo */
				fifo_add(fp64_div(fp64_sd((float)(temp_tim32_ticks + 56)), fp64_sd((float)MAIN_GPS_PPS_AVERAGE_IN_SECONDS)));
			}
		}

		/* trigger on rising edge */
		LED_2_ON;
		gps_timepulse_interrupt_enable(GPS_INTERRUPT_EDGE_FALLING);
	}
	else if (gps_interrupt_edge == GPS_INTERRUPT_EDGE_FALLING) {

		/* trigger on falling edge */
		LED_2_OFF;
		gps_timepulse_interrupt_enable(GPS_INTERRUPT_EDGE_RISING);
	}
}

ISR(TIMER1_OVF_vect)
{
	/* ISR called on hardware timer (1) overflow */
	tim32_ticks += 65536;
}
