// max261 command & control

#include <avr/io.h>
#include <util/delay_basic.h>


uint8_t filtermode[2] ;

// MAX261 data bits 0/1 are on PD01
// MAX261 address bits 0123 are on PD2345
// WR signal is on PD7.
// The filters should operate in
// mode 3 (LP,HP,BP) (2 binary)

// initialize hardware
// just make sure PD7 is 1.
void init_max261() {
	DDRD=0xff ;  // all PD pins are outputs
	PORTD |= (1<<PD7) ;

}


// do a logic-low pulse on the WR signal of the filter chip
// this is located on PD7.
inline void wr_pulse() {
	PORTD &= 0b01111111 ;
	_delay_loop_1(6) ;
	PORTD |= 0b10000000 ;
	// _delay_loop_1(6) ;
}

// set filter mode/configuration
void set_mode(uint8_t mode, uint8_t filter) {
	filtermode[filter]=mode;
}


// write filter frequency (f) to filter bank A/B (ab)
void max261_write_f(uint8_t f, uint8_t ab) {
	uint8_t addr=0;	// register location 0-3
	uint8_t pd=0; // ioport data word
	f = f << 2 ;	
	f |= filtermode[ab];
	
	for (addr = 0 ; addr < 4 ; addr++ ) {	// addresses 0-3 are Q data values
		pd=addr << 2 ;	// shift address up two bits
		pd |= (f & 0b00000011) ;	// add the two data bits
		pd |= (ab << 5) ;	// add filter select bit to A3
		PORTD &= 0b11000000 ;
		PORTD |= pd ;
		wr_pulse();
		f = f >> 2 ;  // shift down data for next cycle
	}
	
}

// write filter Q value (q) to filter A/B (ab)
void max261_write_q(uint8_t q, uint8_t ab) {
	uint8_t addr=0;	// register location 0-3
	uint8_t pd=0; // ioport data word

	if ( q == 0 ) {
		q = 1;	// prevent total filter shutdown if Q=0 in filter A.
	}
	
	for (addr = 4 ; addr < 8 ; addr++ ) {	// addresses 4-7 are Q data values
		pd=addr << 2 ;	// shift address up two bits
		pd |= (q & 0b00000011) ;	// add the two data bits
		pd |= (ab << 5) ;	// add filter select bit to A3
		PORTD &= 0b11000000 ;
		PORTD |= pd ;
		wr_pulse();
		q = q >> 2 ;  // shift down data for next cycle
	}
}
