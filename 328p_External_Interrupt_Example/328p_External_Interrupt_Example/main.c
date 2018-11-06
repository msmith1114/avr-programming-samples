/*
Demo of using interrupts for doing what they do best --
two things at once.
Flashes LED0 at a fixed rate, interrupting whenever button is pressed.
 */

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Button defines */
#define BUTTON                  PIND2
#define BUTTON_PIN              PIND
#define BUTTON_PORT				PORTD

/* LED defines */
#define LED_DDR					DDRB
#define LED_PORT				PORTB 
#define LED2					PINB2
#define LED1					PINB1

ISR(INT0_vect) {         /* Interrupt Routine */
  if (bit_is_clear(BUTTON_PIN, BUTTON)) {
    LED_PORT |= (1 << LED2);
  }
  else {
    LED_PORT &= ~(1 << LED2);
  }
}

void initInterrupt0(void) {
  EIMSK |= (1 << INT0);                                 /* enable INT0 */
  EICRA |= (1 << ISC00);                /* trigger when button changes */
  sei();                          /* set (global) interrupt enable bit */
}

int main(void) {
  // -------- Inits --------- //
  LED_DDR = 0xff;                                   /* Turn on PB1 */
  BUTTON_PORT |= (1 << BUTTON);                     /* pullup */
  initInterrupt0();

  // ------ Event loop ------ //
  while (1) {

    _delay_ms(200);
    LED_PORT ^= (1 << LED1);						/* Toggle LED1 On and Off */

  }                                                 
  return 0;                            
}