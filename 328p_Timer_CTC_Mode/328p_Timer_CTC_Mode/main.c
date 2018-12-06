/*
 * 328p_Timer_CTC_Mode.c
 *
 * Created: 11/9/2018 7:32:35 PM
 * Author : smith
 */ 


#include <avr/io.h>

/* LED Definitions */
#define LED			PINB1
#define LED_PORT	PORTB
#define LED_DDR		DDRB



/***
We are going to use the Atmega's Timer1 (16-bit timer) in Clear Timer on Compare Match (CTC)

For Timer1:
- Setting the mode to (CTC) mode we use OCR1A to set Resolution 
- TCNT1 is cleared when the counter matches the value in OCR1A
- Setting Clock prescaler to clk/1024 = 1MHz/1024 = 1.024 (ms) per tick

***/
static inline void initTimer1CTC(void) {
	TCCR1A |= (1 << WGM12);					/* Set CTC Mode, see page: 141 on Datasheet */
	TCCR1A |= (1 << COM1A0);				/* Toggle OC1A Pin (Pin 12, PD6) after each "cycle" after matching OCR1A */
	TCCR1B |= (1 << CS12) | (1 << CS10);	/* Set Timer1 to clk/1024 prescaler */
}




int main(void)
{
	initTimer1CTC();
	LED_DDR |= (1 << LED) ;			/* PB1 set to output (LED), for OC1A pin to toggle */
	uint16_t duration =  5000;
	OCR1A |= duration;
	while (1)
	{
		/* Toggle should happen after OCR1A value is reached each time */   
	}


	return 0;
}



