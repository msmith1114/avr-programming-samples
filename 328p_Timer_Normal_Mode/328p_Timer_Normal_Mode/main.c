/*
 * 328p_Timer_Normal_Mode.c
 *
 * Created: 11/7/2018 9:07:27 PM
 * Author : smith
 */ 

#include <avr/io.h>

/* LED Definitions */
#define LED			PINB1
#define LED_PORT	PORTB	
#define LED_DDR		DDRB

/* Button Definitions */
#define BUTTON		PIND7
#define BUTTON_PORT	PORTD
#define BUTTON_DDR	DDRD
#define BUTTON_PIN  PIND




/***
We are going to use the Atmega's Timer0 (8-bit timer) and Timer1 (16-bit timer) 

For Timer0:
- Setting the mode to (Normal) mode. Top will be 0xFF (255 steps)
- TCCR0A at Default (Sets to Normal Mode,  Output Compare pin (OC0A/OC0B) are disconnected)
- Setting Clock prescaler to clk/1024 = 1MHz/1024 = 1.024 (ms), each tick is around 1 ms

For Timer1:
- Setting the mode to (Normal) mode. Top will be 0xFFFF (65,535 steps)
- TCCR1A at Default (Sets to Normal Mode,  Output Compare pin (OC1A/OC1B) are disconnected)
- Setting Clock prescaler to clk/256 = 1MHz/256 = 1673 (ms), each tick is around 16 seconds


***/
static inline void initTimer0(void) {
	TCCR0B |= (1 << CS02) | (1 << CS00);	/* Set Timer0 to clk/1024 prescaler */
}

static inline void initTimer1(void) {
	TCCR1B |= (1 << CS12);	/* Set Timer1 to clk/256 prescaler */
}

void timerChoose(uint8_t timer_switch){		/* Determines which timer to use */
	if(timer_switch == 0) {
		initTimer0();
	}
	else {
		initTimer1();
	}
}


int main(void)
{
	LED_DDR |= (1 << LED) ;			/* PB1 set to output (LED) */
	BUTTON_PORT |= (1 << BUTTON);	/* Pull PD7 High */
	
	if((BUTTON_PIN & 0x7) == 0x00) { /* If button is pressed (PD7 low) then we initialize with Timer0, otherwise use Timer1 */
		timerChoose(0);
		    while (1)
		    {
			    if((TIFR0 & 0x01) == 1){ /* When TOV flag in TIFR0 gets set, toggle the LED (This should be around every 255 steps (so 255~ ms or 1/4 a second)) */
				    LED_PORT ^= 0x02;
				    TIFR0 |= (1 << TOV0);
			    }
		    }
		
	}
	else {
		timerChoose(1);
		    while (1)
		    {
			    if((TIFR1 & 0x01) == 1){ /* When TOV flag in TIFR1 gets set, toggle the LED (This should be around every 65,535 steps (so 1673~ ms or 16 seconds)) */
				    LED_PORT ^= 0x02;
				    TIFR1 |= (1 << TOV0);
			    }
		    }
	}

	return 0;
}

