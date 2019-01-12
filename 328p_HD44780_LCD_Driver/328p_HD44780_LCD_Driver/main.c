/*
 * 328p_HD44780_LCD_Driver.c
 *
 * Created: 12/27/2018 10:53:15 PM
 * Author : smith
 */ 

#include <avr/io.h>
#include "HD44780_LCD.h"


int main(void)
{
    /* Replace with your application code */
	initLCD();
	
	/* Display On/Off Control (All turned off initially)  */
	sendNibble(LCD_DISPLAY_CONTROL|DISPLAY_ON|CURSOR_ON|BLINK_ON,INSTRUCTION_REGISTER);
	/***********************************************************************/
	
	// Write HELLO
	/*****************************************/
	putChar('H');
	putChar('E');
	putChar('L');
	putChar('L');
	putChar('O');
	/*****************************************/
	char *msg = " Success!";
	char *p = msg;
	writeString(p);
	lcd_clear();
	lcd_cursor_right();
	lcd_cursor_right();
	lcd_cursor_right();
	putChar('H');
	lcd_cursor_right();
	putChar('P');
	lcd_cursor_left();
	_delay_ms(2000);
	lcd_home();
	
	
    while (1) 
    {
    }
}

