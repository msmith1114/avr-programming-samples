/*
 * 328p_Button_Blink.c
 *
 * Created: 11/6/2018 8:51:42 PM
 * Author : smith
 */ 

#include <avr/io.h>


int main(void)
{
	/* Initialize the data direction register for Port B */
	DDRB = 0b00000010; // Setting Pin "1" to Output (Also notice Pin "0" in Input now, since it is a zero)
	PORTB = 0b00000001;
	while(1)
	{
		if((PINB & 0b00000001) == 0)
		{
			PORTB = 0b00000010;
		}
		else
		{
			PORTB = 0b00000001;
		}
	}
	return 0; //We should never reach this
}

