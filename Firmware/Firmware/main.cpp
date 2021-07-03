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

//Constants for reading in the IR command
#define AGC_PULSE 8000
#define LONG_PULSE 3500
#define ONE_PULSE 1350
#define STOP_BIT 500

struct IR_cmd
{
	char addr;
	char cmd;
};

const int delay = 1000;
int change = 0;

void blink()
{
	PORTB |= 0x02;
	_delay_ms(delay);
	PORTB &= ~0x02;
}

//waits until the interrupt pin is triggered and records how long the device waited for a response in us
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
	return count / 10;
}

//Record the length of 1 pulse of a square wave
int record_square_wave()
{
	int length;
	wait_until_change();
	length = wait_until_change();
	return length;	
}

//Read in a single bit of the IR code based on the length of the square wave
char read_bit()
{
	int length;
	length = record_square_wave();
	if(length < ONE_PULSE)
		return 0x00;
	else
		return 0x01;
}

char read_byte()
{
	char output = 0x00;
	for(int i = 0; i < 8; i++)
		output |= read_bit() << (7 - i);

	return output;
}

IR_cmd IR_Recv()
{
	int length;
	IR_cmd output;
	IR_cmd inv_output;

	//Wait for the beginning of the AGC pulse
	length = record_square_wave();
	
	//Reject command if nothing the AGC isn't long enough
	if(length < AGC_PULSE)
	{
		output.addr = 0;
		output.cmd = 0;
		return output;
	}
	
	//Record the length of the pause & set scanning mode from active high to active low
	length = wait_until_change();

	//Return 0, 0 for repeat commands 
	//TODO: implement code to read repeat commands
	if(length < LONG_PULSE)
	{
		//wait until the stop bit ends
		wait_until_change();

		output.addr = 0;
		output.cmd = 0;
		return output;
	}

	//Read the address
	output.addr = read_byte();

	//Read the inverted address 
	inv_output.addr = read_byte();
	
	//Read the command
	output.cmd = read_byte();

	//Read the inverted output
	inv_output.cmd = read_byte();
	
	//Wait until the stop bit ends
	length = wait_until_change();

	//Check for error conditions regarding the inverted bits & the length of the stop bit
	if
	(
		output.addr != ~(inv_output.addr) || 
		output.cmd != ~(inv_output.cmd) || 
		length < STOP_BIT
	)
	{
		output.addr = 0;
		output.cmd = 0;
		return output;
	}
	
	return output;
}

void USI_init()
{
	//Set Two-Wire mode
	USICR |= _BV(USIWM1);

	//Set software clock mode for simplicity
	USICR |= _BV(USICLK);
}

void USI_Write(char data)
{
	USIDR = data;
	
	for(int i = 0; i < 8; i++)
	{
		//Send a bit
		USICR |= _BV(USICLK);

		//Pulse a square wave on the SCL line
		USICR |= _BV(USITC);
		_delay_us(100);
		USICR |= _BV(USITC);
		_delay_us(100);
	}
}

int main(void)
{
	DDRB = 0x02; 
	MCUCR |= _BV(ISC00);
	IR_cmd remote_cmd;
	remote_cmd.addr = 0x00;
	remote_cmd.cmd = 0x00;

	USI_init();

	sei();

	while(1)
	{
		remote_cmd = IR_Recv();
		if(remote_cmd.cmd == 0x16) blink();
		cli();
		USI_Write(remote_cmd.cmd);
		sei();
	}
}

ISR(INT0_vect)
{
	change = TRUE;
}