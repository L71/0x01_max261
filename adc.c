// ADC handling

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "max261.h"
#include "lookuptable.h"

// setup interrupt timer
void run_adc_timer() {
	
	OCR1AH = 0x13;	// 20000000/5000 -> 4KHz timer
	OCR1AL = 0x88;  // this means every CV / Pot will be read & updated at 1 KHz.
	
	// clear on OCR1A hit, prescaler=1.
	TCCR1B |= (1<<WGM12) | (1<<CS10) ;
	
	// enable OCR1A interrupt
	TIMSK1 |= (1<<OCIE1A);
	
}


// setup ADC & trigger first conversion
void setup_adc() {

	// enable ADC, prescaler = /64 -> 312.5 KHz ADC clock. 
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) ; 
	
	// disable digital IOs on used ADC pins
	DIDR0 = 0x0f ;
	
	// v.ref = AREF, left adjust, channel selected=0.
	ADMUX |= (1<<ADLAR) | (1<<REFS0) ;
	
	// go conversions!
	ADCSRA |= (1<<ADSC) ;

}

// ADC interrupt handler & next-conversion-trigger
ISR(TIMER1_COMPA_vect) {

	// ISR indicator
	// PORTB |= 0b00000001;
	
	static uint8_t adc_chan = 0 ;		// currently selected ADC channel
	static uint8_t adc_last_value[4];
	uint8_t adc_mask = 0b00000011 ; 	// mask of bits used for ADC channel selection
	
	// read ADC register(s)
	uint8_t adc_in = ADCH ;
	uint8_t adc_in_neg = 255-adc_in ;
	
	if ( adc_in != adc_last_value[adc_chan] ) {	// only update if input has changed
		// PORTB |= 0b00000001; 
		switch (adc_chan) {
			case 0 :	// filter A F
				max261_write_f(adc_in >> 2, 0);
				OCR0A = pgm_read_byte(&divider[adc_in_neg]);
				TCCR0B = pgm_read_byte(&prescaler[adc_in_neg]);
				break ;
			
			case 1 :	// filter A Q
				max261_write_q((adc_in_neg >> 1), 0);
				break ;
			
			case 2 :	// filter B F
				max261_write_f(adc_in >> 2, 1);
				OCR2A = pgm_read_byte(&divider[adc_in_neg]);
				TCCR2B = pgm_read_byte(&prescaler[adc_in_neg]);
				break ;
			
			case 3 :	// filter B Q
				max261_write_q((adc_in_neg >> 1), 1);
				break;
		}
	} 
	
	// save adc value for next time...
	adc_last_value[adc_chan] = adc_in;
	
	// channel number +1
	adc_chan = ((adc_chan+1) & adc_mask ) ;
	
	// update ADMUX register
	ADMUX &= 0xf0;	// reset channel bits
	ADMUX |= adc_chan ;
	
	// start next conversion
	ADCSRA |= (1<<ADSC) ;
	
	// turn off ISR indicator
	// PORTB &= 0b11111110;
}

