/*
 * HD44780_LCD.h
 *
 * Created: 12/27/2018 10:54:00 PM
 *  Author: smith
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#define DB4			4
#define DB5			5
#define DB6			6
#define DB7			7
#define RS			0
#define RW			1
#define EN			2

#define LCD_DDR		DDRD
#define LCD_PORT	PORTD


enum mode {
	INSTRUCTION_REGISTER,
	DATA_REGISTER
	};

/* Delays */
/* All Delays noted in microseconds */
#define LCD_ENABLE_PULSE_DELAY			1000
#define LCD_POWER_ON_DELAY				100000
#define LCD_POWER_ON_FUNCTION_SET_DELAY	5000
#define LCD_FUNCTION_SET_SPECIAL_DELAY	150
#define LCD_FUNCTION_SET_DELAY			60
#define LCD_DISPLAY_CONTROL_DELAY		60
#define LCD_CLEAR_DISPLAY_DELAY			3500
#define LCD_ENTRY_MODE_SET_DELAY		60
/**************************************/


/* The following represent the hex values for instruction options as well as the value for the instruction itself */

/* Clear Display */
#define LCD_DISPLAY_CLEAR		0x01
/**************************************/

/* Return Home */
#define LCD_RETURN_HOME			0x02
/**************************************/

/* Display On/Off Control */
#define LCD_DISPLAY_CONTROL		0x08	
#define DISPLAY_ON				0x04
#define DISPLAY_OFF				0x00
#define CURSOR_ON				0x02
#define CURSOR_OFF				0x00	
#define BLINK_ON				0x01
#define BLINK_OFF				0x00
/**************************************/

/* Entry Mode Set */
#define LCD_ENTRY_MODE			0x04
#define INC_ADDRESS				0x02
#define	DEC_ADDRESS				0x00
/* 
Note: If using SHIFT_DISPLAY_X, you do NOT want to set INC_ADDRESS or DEC_ADDRESS also as it changes I/D as well
S (Shift) being 0 assumes no shift, so this assumes Shift is (1) and I/D is set with it.

You can use INC_ADDRESS or DEC_ADDRESS on it's own however if we are assuming no shifting
*/
#define SHIFT_DISPLAY_RIGHT		0x01		
#define SHIFT_DISPLAY_LEFT		0x03
/**************************************/

/* Function Set */
#define LCD_FUNCTION_SET		0x20
#define	MODE_4BIT				0x00
#define MODE_8BIT				0x08
#define DISPLAY_2_LINE			0x08
#define DISPLAY_1_LINE			0x00
#define FONT_5x8_DOTS			0x00
#define	FONT_5x10_DOTS			0x04
/* Note: Cannot display two lines for 5x10 dot character font */
/**************************************/

/* Cursor/Display Shift */
#define LCD_CURSOR_SHIFT		0x10
#define CURSOR_SHIFT_LEFT		0x00
#define	CURSOR_SHIFT_RIGHT		0x04
#define DISPLAY_SHIFT_LEFT		0x08
#define DISPLAY_SHIFT_RIGHT		0X0C
/**************************************/


void initLCD(void);
void sendNibble(uint8_t data, uint8_t mode);
void toggleEnable(void);
void putChar(char c);
void writeString(char *s);
void lcdInstruction(uint8_t cmd);

// Helper Functions
void lcd_clear(void);
void lcd_home(void);
void lcd_cursor_right(void);
void lcd_cursor_left(void);
