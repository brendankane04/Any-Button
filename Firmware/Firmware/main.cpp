//Remote Control Receiver Momentary+Alternate Original ATtiny13A 20191021 2200
//PB1,PB2 : Momentary Operation
//PB3,PB4 : Alternate Operation

#ifndef F_CPU
#define F_CPU 8000000UL
#endif 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FALSE 0
#define TRUE  1

#define SCL 0x08
#define SDA 0x10

//Constants for reading in the IR command
#define AGC_PULSE 7500
#define LONG_PULSE 3000
#define ONE_PULSE 1200
#define STOP_BIT 400

struct IR_cmd
{
	char addr;
	char cmd;
};

void Write(char);

const int delay = 1000;

void blink()
{
	PORTB |= 0x02;
	_delay_ms(delay);
	PORTB &= ~0x02;
	_delay_ms(delay);
}

//waits until the interrupt pin is triggered and records how long the device waited for a response in us
int wait_until_change()
{
	int count = 0;
	GIFR |= _BV(INTF0); //Clear the flag before starting
	while((GIFR & _BV(INTF0)) == 0)
	{
		//Increment & reset when it's been increasing for too long
		count++;
		_delay_us(10);
	}
	GIFR |= _BV(INTF0); //Clear the flag after its use
	return count * 10;
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

//Read in a byte
char read_byte()
{
	char output = 0x00;
	for(int i = 0; i < 8; i++)
		output |= read_bit() << (7 - i);

	return output;
}

//Read in an IR command & address
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
		output.cmd = 1;
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
		output.cmd = 2;
		return output;
	}

	//Read the address
	output.addr = read_byte();
	
	Write(output.addr);
	return output;

	//Read the inverted address 
	inv_output.addr = read_byte();
	
	//Read the command
	output.cmd = read_byte();

	//Read the inverted output
	inv_output.cmd = read_byte();
	
	//Wait until the stop bit ends
	length = wait_until_change();

	Write(output.addr);
	_delay_ms(500);
	Write(inv_output.addr);

	_delay_ms(1000);

	Write(output.cmd);
	_delay_ms(500);
	Write(inv_output.cmd);

	//Check for error conditions regarding the inverted bits & the length of the stop bit
	if
	(
		output.addr != ~(inv_output.addr) || 
		output.cmd != ~(inv_output.cmd)  
		//length < STOP_BIT
	)
	{
		output.addr = 0;
		output.cmd = 3;
		return output;
	}
	
	return output;
}

void Write(char data)
{
	char curr;
	for(int i = 0; i < 8; i++)
	{
		//Get the current bit
		curr = (data >> (7 - i)) & 0x01;

		//Send out the bit
		if(curr)
			PORTB |= SDA;
		else
			PORTB &= ~SDA;

		PORTB |= SCL;
		_delay_us(100);
		PORTB &= ~SCL & ~SDA;
		_delay_us(100);
	}

	//Clear data line
	PORTB &= ~SDA;
}

void interrupt_init()
{
	//Initialize the interrupt mode for INT0
	MCUCR |= _BV(ISC00); 
	//GIMSK |= _BV(INT0);
}

void timer_init()
{
	//Normal mode of counting
	

	//Set the prescaler to 1024
	TCCR0B |= _BV(CS02) | _BV(CS00);

}

int main(void)
{
	//Set LED pin as an output
	DDRB |= 0x02; 

	interrupt_init();

	//Initialize an empty IR command
	IR_cmd remote_cmd;
	remote_cmd.addr = 0x00;
	remote_cmd.cmd = 0x00;

	//Initialize the bit-bang write command
	DDRB |= SDA | SCL;
	PORTB |= SCL;

	sei();

	int length = 0;
	while(1)
	{
		remote_cmd = IR_Recv();
		if(remote_cmd.cmd == 0x16) blink();
		blink();
	}
}
