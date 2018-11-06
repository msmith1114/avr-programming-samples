/*
 * 328p_UART_Example.c
 *
 * Created: 10/27/2018 2:14:06 AM
 * Author : smith
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "USART.h"


// -------- Functions --------- //
static inline void initADC0(void) {
	ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS2);                   /* ADC clock prescaler /16 */
	ADCSRA |= (1 << ADEN);                                 /* enable ADC */
}


int main(void)
{
	
	// -------- Inits --------- //
	  uint16_t adcValue;
	  char serialCharacter;
	  initUSART();
	  initADC0();
	
	/* --- Event Loop --- */
    while (1) 
    {

		ADCSRA |= (1 << ADSC);                     /* start ADC conversion */
		loop_until_bit_is_clear(ADCSRA, ADSC);          /* wait until done */
		adcValue = ADC;                                     /* read ADC in */
		
		_delay_ms(1000);
		printWord(adcValue);
    }
	return 0;
}

