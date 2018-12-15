/*
 * 328p_UART_Example.c
 *
 * Created: 10/27/2018 2:14:06 AM
 * Author : smith
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "USART.h"




int main(void)
{
	char serialCharacter;

	// -------- Inits --------- //
	initUSART();
	printString("Hello World!\r\n");                          /* to test */
	
	/* --- Event Loop --- */
    while (1) 
    {
		serialCharacter = receiveByte();
		transmitByte(serialCharacter);
    }
	return 0;
}

