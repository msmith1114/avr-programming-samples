/*
 * i2c.c
 *
 * Created: 12/15/2018 2:07:30 AM
 *  Author: smith
 */ 

#include <avr/io.h>

void initI2C(void);

void sendStart(void);

void sendStop(void);

void checkStatus(void);

void sendAddress(uint8_t address);

void sendData(uint8_t data);

uint8_t receiveData(void);

uint8_t receiveDataAndStop(void);