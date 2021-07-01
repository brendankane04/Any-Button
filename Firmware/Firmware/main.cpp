//Remote Control Receiver Momentary+Alternate Original ATtiny13A 20191021 2200
//PB1,PB2 : Momentary Operation
//PB3,PB4 : Alternate Operation

#ifndef F_CPU
#define F_CPU 1000000UL
#endif 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FALSE 0
#define TRUE  1

struct IR_cmd
{
	int addr;
	int cmd;
};

const int delay = 1000;
int change = 0;

void blink()
{
	PORTB |= 0x02;
	_delay_ms(delay);
	PORTB &= ~0x02;
}

//waits until the interrupt pin is triggered and records how long the device waited for a response in 10's of microseconds
int wait_until_change()
{
	int count = 0;
	GIMSK |= _BV(INT0);
	while(!change)
	{
		//Increment & reset when it's been increasing for too long
		count++;
		if(count == 1500) count = 0;

		_delay_us(10);
	}
	change = FALSE;
	GIMSK &= ~_BV(INT0);
	return count;
}

//Record the length of 1 pulse of a square wave
int record_square_wave()
{
	int length;
	wait_until_change();
	length = wait_until_change();
	return length;	
}

IR_cmd IR_Recv()
{
	
}

int main(void)
{
	DDRB = 0x02; 
	MCUCR |= _BV(ISC00);
	int length = 0;
	sei();

	while(1)
	{
		length = wait_until_change();
		if(length > 10) blink();
	}
}

ISR(INT0_vect)
{
	change = TRUE;
}