/* 
* BB_I2C.cpp
*
* Created: 7/7/2021 11:03:41 PM
* Author: brend
*/

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "BB_I2C.h"

// default constructor
BB_I2C::BB_I2C(int sda, int scl)
{
	//Set the pins which the interface is using
	this->SDA = _BV(sda);
	this->SCL = _BV(scl);

	//Set the SDA & SCL pins on PORTB as outputs
	DDRB |= SDA | SCL;

	//Set SCL to high
	PORTB |= SCL;
}

void BB_I2C::write(char data)
{
	char curr;

	//Start bit
	PORTB &= ~SCL;
	_delay_us(100);

	for(int i = 0; i < 8; i++)
	{
		//Get the current bit
		curr = (data >> (7 - i)) & 0x01;

		//Turn on the clock cycle
		PORTB |= SCL;

		//Send out the bit
		if(curr) PORTB |= SDA;
		else	 PORTB &= ~SDA;
		_delay_us(100);

		//Pull the data bit & clock cycle to low
		PORTB &= ~SCL & ~SDA;
		_delay_us(100);
	}

	//Clear data line
	PORTB &= ~SDA;
	//Start bit
	PORTB |= SCL;
}
