//Remote Control Receiver Momentary+Alternate Original ATtiny13A 20191021 2200
//PB1,PB2 : Momentary Operation
//PB3,PB4 : Alternate Operation

#ifndef F_CPU
#define F_CPU 1000000UL
#endif 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "IR_NEC.h"

int main( void )
{
	DDRB = 0x02; 
	const int delay = 1000;
	IR_init(100);
	sei();

	while(1)
	{
		PORTB |= 0x02;
		_delay_ms(delay);
		PORTB &= ~0x02;
		_delay_ms(delay);
		IR_data_ready();
	}
}