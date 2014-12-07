// filter clock generation timer setup & stuff

#include <avr/io.h>

// setup timer0 and timer2 for frequency generation
// output on capture/compare output A from both timers.
void setup_f_timer() {
	
	// Timer 0 setup
	DDRD |= (1<<DDD6) ;	//OC0A = PD6
	TCCR0A |= (1<<COM0A0) | (1<<WGM01) ;
	TCCR0B |= (1<<CS00) ;
	OCR0A = 200 ; // should give 50KHz output clock
	
	// Timer 2 setup
	DDRB |= (1<<DDB3) ;	//OC2A = PB3
	TCCR2A |= (1<<COM2A0) | (1<<WGM21) ;
	TCCR2B |= (1<<CS20) ;
	OCR2A = 100 ; // should give 100KHz output clock
	

}
