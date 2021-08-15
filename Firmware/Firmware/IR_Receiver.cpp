/* 
* IR_Receiver.cpp
*
* Created: 7/7/2021 6:06:22 PM
* Author: brend
*/

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "IR_Receiver.h"

int IR_Receiver::wait_until_change()
{
	//Initialize the clock, set up time, & the prescaler even if the DIV8 fuse is set.
	//The ATITNY85 comes shipped underclocked, which is too slow for the IR NEC protocol
	//Essentially, speed up the clock if it isn't fast enough
	CLKPR |= 0x80; //Enable changes on the CLKPR register
	CLKPR &= ~0x0F; //Set the prescaler to 1
	
	int count = 0;
	GIFR |= _BV(INTF0); //Clear the flag before starting
	while((GIFR & _BV(INTF0)) == 0)
	{
		//Increment
		count++;
		_delay_us(10);
	}
	GIFR |= _BV(INTF0); //Clear the flag after its use
	return count * 10;
}

int IR_Receiver::measure_square_wave()
{
	int length;
	wait_until_change();
	length = wait_until_change();
	return length;	
}

char IR_Receiver::read_bit()
{
	int length;
	length = measure_square_wave();
	if(length < ONE_PULSE)
		return 0x00;
	else
		return 0x01;
}

char IR_Receiver::read_byte()
{
	char output = 0x00;
	for(int i = 0; i < 8; i++)
	output |= read_bit() << i;

	return output;
}

IR_Receiver::IR_Receiver()
{
	IR_Receiver(7);
}

IR_Receiver::IR_Receiver(int pin)
{
	//Set up the interrupt on the INT0 pin to receive the IR signal
	//Initialize the interrupt mode for INT0
	MCUCR |= _BV(ISC00);
}

IR_Receiver::IR_cmd IR_Receiver::recv()
{
	int length;
	IR_cmd output;
	IR_cmd inv_output;

	//Wait for the beginning of the AGC pulse
	length = measure_square_wave();

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
	
	//Read the inverted address
	inv_output.addr = read_byte();
	
	//Read the command
	output.cmd = read_byte();

	//Read the inverted output
	inv_output.cmd = read_byte();
	
	//Wait until the stop bit ends
	wait_until_change();

	//Check for error conditions regarding the inverted bits
	//Return 0, -1 if a transmission error occurs
	if
	(
	output.addr != ((unsigned char) ~inv_output.addr) ||
	output.cmd != ((unsigned char) ~inv_output.cmd)
	)
	{
		output.addr = 0;
		output.cmd = -1;
		return output;
	}
	
	return output;
}
