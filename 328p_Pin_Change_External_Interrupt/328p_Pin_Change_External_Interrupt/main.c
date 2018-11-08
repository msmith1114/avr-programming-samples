/*
	Demonstrates using pin-change interrupts on PB0 to light an LED (on PB1)
 */

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Button defines */
#define BUTTON                  PINB0
#define BUTTON_PIN              PINB
#define BUTTON_PORT				PORTB

/* LED defines */
#define LED_DDR					DDRB
#define LED_PORT				PORTB 
#define LED1					PINB1

ISR(PCINT0_vect) {         /* Interrupt Routine */
  if (bit_is_clear(BUTTON_PIN, BUTTON)) {
    LED_PORT |= (1 << LED1);
  }
  else {
    LED_PORT &= ~(1 << LED1);
  }
}

void initInterrupt0(void) {
  PCICR |= (1 << PCIE0);								/* set pin-change interrupt for B pins */
  PCMSK0 |= (1 << PCINT0);                              /* set mask to look for PB0 */
  sei();												/* set (global) interrupt enable bit */
}

int main(void) {
  // -------- Inits --------- //
  LED_DDR = 0x02;                                   /* set PB1 to Output and PB0 to Input */
  BUTTON_PORT |= (1 << BUTTON_PIN);                 /* pullup */
  initInterrupt0();

  // ------ Event loop ------ //
  while (1) {
													/* do nothing */														
  }                                                 
  return 0;                            
}