/*
 * 328p_Blink.c
 *
 * Created: 10/15/2018 1:38:22 AM
 * Author : smith
 */ 

#define F_CPU 1600000UL

#include <avr/io.h> //Defines pins, ports, etc.
#include <util/delay.h>

#define LED_PORT PORTB
#define LED_PIN PINB2


int main(void)
{
	DDRB |= (1 << PINB2); //Data Direction Register B: writing a 1 to the bit enables output

	while (1) {
		PORTB |= (1 << PINB2);
		_delay_ms(1000); //creates a 1-second delay
		PORTB &= ~(1 << PINB2);
		_delay_ms(1000); //creates another 1-second delay
	}

	return (0); //this line is never actually reached
}






