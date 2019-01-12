/*
 * 328p_I2C_Driver_Sample.c
 *
 * Created: 12/15/2018 2:06:51 AM
 * Author : smith
 */ 

#include <avr/io.h>
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
    initUSART();
    printString("I2C Starting\r\n");
    _delay_ms(2000);
    initI2C();
    while (1) 
    {
		sendStart();
		checkStatus();
		sendData(MCP9808_ADDRESS_W);
		sendData(MCP9808_AMBIENT_TEMP_REGISTER);
		printString("Address and Register Sent, Entering receive mode...\r\n");
		_delay_ms(5000);
		sendStart();
		checkStatus();
		sendData(MCP9808_ADDRESS_R);
		UpperByte = receiveData();
		LowerByte = receiveDataAndStop();
		sendStop();
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
		_delay_ms(5000);
		
    }
}

