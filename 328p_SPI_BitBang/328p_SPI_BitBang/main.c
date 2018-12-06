/*
 * 328p_SPI_BitBang.c
 *
 * Created: 11/29/2018 10:59:43 PM
 * This is only for Mode 0 of SPI and is not meant to be anything but a basic test
 */ 

#include <avr/io.h>
#include <avr/delay.h>

/* Macro's */
#define _BV(bit)    (1 << (bit)) 

/* SPI Port Defines */
#define SCLK		PINC5	
#define MOSI		PINC4
#define MISO		PINC3
#define SS			PINC2

/* SPI DDR/PINS */
#define SPI_DDR		DDRC
#define SPI_PORT	PORTC
#define SPI_PIN		PINC

/* Button DDR/PORT/PIN */
#define BTN_DDR		DDRB
#define BTN_PORT	PORTB	
#define BTN_PIN		PINB
#define BUTTON		PINB1



#define F_CPU 1000000UL

void enable_SPI(void) {
	SPI_DDR = 0b00110100;			/* Set SS/MOSI/SCLK to Output, MISO to Input */
}


void ss_low(void) {
	SPI_PORT &= ~(1 << SS);
}

void ss_high(void) {
	SPI_PORT |= (1 << SS);
}


void sclk_high(void) {
	SPI_PORT |= (1 << SCLK);
}

void sclk_low(void) {
	SPI_PORT &= ~(1 << SCLK);
}

void mosi_high(void) {
	SPI_PORT |= (1 << MOSI);
}

void mosi_low(void) {
	SPI_PORT &= ~(1 << MOSI);
}

unsigned char transmit_byte(unsigned char data_byte) {
	
	int i;
	char ret_data;

	_delay_ms(100);
	
	/* SCLK Currently holding low, MOSI is low, SS is low */
	for(i = 0; i < 8; i++) {
		loop_until_bit_is_clear(BTN_PIN,BUTTON);
		_delay_ms(1000);
		sclk_low(); //Set Low
		if(data_byte & 0x80) {
			mosi_high();
		}
		else {
			mosi_low();
		}
		/* MOSI Value is latched in */
		sclk_high(); //Send High
		data_byte <<= 1; //MSB First
		if(PINB & MISO) {
			ret_data |= 1;
		}
		ret_data <<=1; //Shift Left
	}
	ss_high(); // Pull Slave-Select back up
	sclk_low(); // Set Clock back to idle (0 in our case for mode 0)
	return ret_data;
	
}

int main(void)
{
	/* Initialize the data direction register for Port B */
	BTN_DDR = 0b00000000;				/* Setting Pin "1" to Input	*/
	BTN_PORT = 0b00000010;				/*	PUR on PB1	*/
	/*													*/
	
	ss_low();							/* Set SS Low */
    enable_SPI();						/* Set up correct Data Direction Ports */
    while (1) 
    {
		transmit_byte('M'); 
    }
}

