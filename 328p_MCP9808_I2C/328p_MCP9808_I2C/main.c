/*
 * 328p_MCP9808_I2C.c
 *
 * Created: 12/11/2018 11:45:53 PM
 * Author : smith
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "USART.h"


#define MCP9808_ADDRESS_W               0b00110000
#define MCP9808_ADDRESS_R               0b00110001
#define MCP9808_AMBIENT_TEMP_REGISTER	0b00000101



int main(void)
{
	uint8_t UpperByte, LowerByte;
	uint16_t Temperature;
	clock_prescale_set(clock_div_1);                             /* 8MHz */
	initUSART();
	printString("I2C Starting\r\n"); 
	_delay_ms(20000); 
	initI2C();
    while (1) 
    {
		i2cStart();
		i2cWaitForComplete();
		i2cSend(MCP9808_ADDRESS_W);
		i2cWaitForComplete();
		i2cSend(MCP9808_AMBIENT_TEMP_REGISTER);
		i2cWaitForComplete();
		i2cStart();
		i2cWaitForComplete();
		i2cSend(MCP9808_ADDRESS_R);
		i2cWaitForComplete();
		UpperByte = i2cReadAck();
		LowerByte = i2cReadNoAck();
		i2cStop();
		UpperByte = UpperByte & 0x1F; //Clear flag bits
		if ((UpperByte & 0x10) == 0x10){ //TA < 0°C
			UpperByte = UpperByte & 0x0F; //Clear SIGN
			Temperature = 256 - (UpperByte * 16 + LowerByte / 16);
		}else //TA 0°C
		Temperature = (UpperByte * 16 + LowerByte / 16);
		//Temperature = Ambient Temperature (°C)
		printString("Upper: "); 
		printByte(UpperByte);
		printString("\r\n"); 
		printString("Lower: "); 
		printByte(LowerByte);
		printString("\r\n"); 
		printString("Temp Celsius: "); 
		printWord(Temperature);
		printString("\r\n"); 
		_delay_ms(20000); 

		
    }
}

