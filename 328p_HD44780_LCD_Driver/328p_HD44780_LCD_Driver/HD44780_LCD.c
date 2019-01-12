/*
 * HD44780_LCD.c
 *
 * Created: 12/27/2018 10:54:09 PM
 *  Author: smith
 */ 
#include "HD44780_LCD.h"

void toggleEnable(void) {
		LCD_PORT |= (1 << EN);
		_delay_us(5000);
		LCD_PORT &= ~(1 << EN);
}

void sendNibble(uint8_t data, uint8_t mode) {
	mode ? (LCD_PORT |= (1 << RS)) : (LCD_PORT &= ~(1 << RS));
	if(data & 0x80) LCD_PORT |= (1 << DB7);
	if(data & 0x40) LCD_PORT |= (1 << DB6);
	if(data & 0x20) LCD_PORT |= (1 << DB5);
	if(data & 0x10) LCD_PORT |= (1 << DB4);
	toggleEnable();
	LCD_PORT = 0x00;
	mode ? (LCD_PORT |= (1 << RS)) : (LCD_PORT &= ~(1 << RS));
	if(data & 0x08) LCD_PORT |= (1 << DB7);
	if(data & 0x04) LCD_PORT |= (1 << DB6);
	if(data & 0x02) LCD_PORT |= (1 << DB5);
	if(data & 0x01) LCD_PORT |= (1 << DB4);
	toggleEnable();
	LCD_PORT = 0x00;
	_delay_us(60);
}

void lcdInstruction(uint8_t cmd) {
	sendNibble(cmd, INSTRUCTION_REGISTER);
}



void putChar(char c) {
	sendNibble(c, DATA_REGISTER);
}

void writeString(char *s) {
	while(*s != '\0') {
		putChar(*s);
		s++;
	}
}




void initLCD(void) {
	LCD_DDR |= (1 << RS) | (1 << RW) | (1 << EN) | (1 << DB4) | (1 << DB5) | (1 << DB6) | (1 << DB7); /* Set all to output */
	
	/* Initial Special Case Function Sets */
	/* DB0-DB3 are ignored, however we are not sending 2 separate nibbles */
	_delay_ms(100); /* Wait 20ms after VDD > 4.5v */
	LCD_PORT = (1 << DB5) | (1 << DB4);
	toggleEnable();
	_delay_us(LCD_POWER_ON_FUNCTION_SET_DELAY);
	
	LCD_PORT = (1 << DB5) | (1 << DB4);
	toggleEnable();
	_delay_us(LCD_FUNCTION_SET_SPECIAL_DELAY);
	
	LCD_PORT = (1 << DB5) | (1 << DB4);
	toggleEnable();
	_delay_us(LCD_FUNCTION_SET_SPECIAL_DELAY);
	
	LCD_PORT = (1 << DB5);
	toggleEnable();
	_delay_us(LCD_FUNCTION_SET_SPECIAL_DELAY);
	/***********************************************************************/
	
	
	/* Real Function Set (Number of Lines/Font */
	sendNibble(LCD_FUNCTION_SET|MODE_4BIT|DISPLAY_2_LINE,INSTRUCTION_REGISTER);
	/***********************************************************************/
	
	/* Display On/Off Control (All turned off initially)  */
	sendNibble(LCD_DISPLAY_CONTROL|DISPLAY_OFF|CURSOR_OFF|BLINK_OFF,INSTRUCTION_REGISTER);
	/***********************************************************************/

	/* Clear Display  */
	sendNibble(LCD_DISPLAY_CLEAR,INSTRUCTION_REGISTER);
	/***********************************************************************/
	
	/* Entry Mode Set  */
	sendNibble(LCD_ENTRY_MODE|INC_ADDRESS,INSTRUCTION_REGISTER);
	/***********************************************************************/
	
	/* Initialization Ends */
}


/***********************************************************************/
/* Helper Functions */
void lcd_clear(void) {
	lcdInstruction(LCD_DISPLAY_CLEAR);
}

void lcd_home(void) {
	lcdInstruction(LCD_RETURN_HOME);
}

void lcd_cursor_right(void) {
	lcdInstruction(LCD_CURSOR_SHIFT|CURSOR_SHIFT_RIGHT);
}

void lcd_cursor_left(void) {
	lcdInstruction(LCD_CURSOR_SHIFT|CURSOR_SHIFT_LEFT);
}

/***********************************************************************/
