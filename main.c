#define F_CPU 20000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "filterclock.h"
#include "max261.h"


void setup_leftover_pins() {
	// enable pull-up resistors on PC4 and PC5
	PORTC |= 0x30;
	
	// same on PB1,PB2 (OC1A, OC1B, LED status pins originally)
	PORTB |= 0x06;
}


int main() {

    // PB0 = output for I'm Alive Blink
    DDRB |= (1<<PB0);

	// blink PB0 LED once.
	PORTB |= 0b00000001;
	_delay_ms(200);
	PORTB &= 0b11111110;
	_delay_ms(200);
	PORTB |= 0b00000001;

	// setup & run system timer
	// setup_system_timer(); // DISABLED.
	
	// start frequency generator timers
	setup_f_timer();

	// initialize filter hw
	init_max261();
	
	// set filter modes (See max261 data sheet for details)
	// 1:  LP, BP, N
	// 2:  LP, BP, N (other characteristics)
	// 3:  LP, BP, HP
	// 4:  LP, BP, AP
	set_mode(2, 0);	// Filter A mode 3
	set_mode(2, 1);	// Filter B mode 3
	max261_write_f(1, 0);	// preset filter A F
	max261_write_f(1, 1);	// preset filter B F
	
	// do something with leftover IO pins
	setup_leftover_pins();
	
	// launch ADC conversions
	setup_adc();
	run_adc_timer();

    // Enable interrupts for all. GO! =)
    SREG |= 0x80 ;
	
    // main loop
    while ( 1 )  {
		PORTB |= 0b00000001;
        _delay_ms(2000);
		PORTB &= 0b11111110;
		_delay_ms(2000);
    }
  
}
