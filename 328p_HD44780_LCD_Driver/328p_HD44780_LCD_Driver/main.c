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
	sendNibble(LCD_DISPLAY_CONTROL|DISPLAY_ON|CURSOR_OFF|BLINK_ON,INSTRUCTION_REGISTER);
	/***********************************************************************/
	uint8_t lock[] = {
		0b01110,
		0b10001,
		0b10001,
		0b11111,
		0b11011,
		0b11011,
		0b11111,
		0b00000
	};
	
	uint8_t bell[] = {
		0b00100,
		0b01110,
		0b01110,
		0b01110,
		0b01110,
		0b11111,
		0b00100,
		0b00000
	};
	
	uint8_t battery_0[] = {
		0b01110,
		0b11011,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b11111
	};
	
	
	uint8_t battery_1[] = {
		0b01110,
		0b11011,
		0b10001,
		0b10001,
		0b10001,
		0b10001,
		0b11111,
		0b11111
	};
	
	
	uint8_t battery_2[] = {
		0b01110,
		0b11011,
		0b10001,
		0b10001,
		0b10001,
		0b11111,
		0b11111,
		0b11111
	};
	
	
	uint8_t battery_3[] = {
		0b01110,
		0b11011,
		0b10001,
		0b10001,
		0b11111,
		0b11111,
		0b11111,
		0b11111
	};
	
	
	uint8_t battery_4[] = {
		0b01110,
		0b11011,
		0b10001,
		0b11111,
		0b11111,
		0b11111,
		0b11111,
		0b11111
	};
	
	
	uint8_t battery_5[] = {
		0b01110,
		0b11111,
		0b11111,
		0b11111,
		0b11111,
		0b11111,
		0b11111,
		0b11111
	};
	/*****************************************/
/*
	writeCustomChar(lock,0);
	writeCustomChar(bell,1);
	writeCustomChar(battery_0,2);
	writeCustomChar(battery_1,3);
	writeCustomChar(battery_2,4);
	writeCustomChar(battery_3,5);
	writeCustomChar(battery_4,6);
	writeCustomChar(battery_5,7);
	lcd_home();
	sendNibble(0x00,DATA_REGISTER);
	sendNibble(0x01,DATA_REGISTER);
	sendNibble(0x02,DATA_REGISTER);
	sendNibble(0x03,DATA_REGISTER);
	sendNibble(0x04,DATA_REGISTER);
	sendNibble(0x05,DATA_REGISTER);
	sendNibble(0x06,DATA_REGISTER);
	sendNibble(0x07,DATA_REGISTER);
	/*****************************************/
	writeString("This is a test");
	lcd_home();
	writeString("clear test!");

	
    while (1) 
    {
    }
}

