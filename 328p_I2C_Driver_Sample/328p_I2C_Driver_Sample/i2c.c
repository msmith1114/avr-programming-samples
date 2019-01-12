/*
 * i2c.h
 *
 * Created: 12/15/2018 2:07:20 AM
 *  Author: smith
 *
 */ 
#include "i2c.h"

void initI2C(void) {
	// Prescale to 1 (0 and 0 for TWPS0/TWPS1 in TWSR
	TWBR = 0x20; // Set to 32
}

void sendStart(void) {
	TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTA));
}

void sendStop(void) {
	TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTO));
}

void checkStatus(void) {
	loop_until_bit_is_set(TWCR,TWINT);
}

void sendData(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	checkStatus();
}

uint8_t receiveData() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	checkStatus();
	return TWDR;
}

uint8_t receiveDataAndStop() {
	TWCR = (1 << TWINT) | (1 << TWEN);
	checkStatus();
	return TWDR;
}
