/* 
* Relay.cpp
*
* Created: 7/7/2021 11:03:29 PM
* Author: brend
*/

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "Relay.h"

#define FALSE 0
#define TRUE  1

// default constructor
Relay::Relay()
{
	Relay(1);
}

Relay::Relay(int pin)
{
	//Initialize the state as off
	state = 0;
	button_state = 0;

	//Ensure the pin is one of the 5 possibilities & set the pin for this relay
	if(0 <= pin && pin <= 5)
	this->pin = pin;
	else
	this->pin = 1; //1 is the default pin

	//Set the pin as an output
	DDRB |= _BV(pin);
}

void Relay::toggle()
{
	if(state)
	PORTB &= ~_BV(pin);
	else
	PORTB |= _BV(pin);

	state = !state;
}

void Relay::set(int input)
{
	input = !!input; //Normalize the input to 1 or 0
	if(input != state) toggle(); //Toggle the pin if the goal & current setting are different
}

void Relay::press()
{
	set(FALSE);
	_delay_ms(10);
	set(TRUE);
	_delay_ms(10);
	set(FALSE);
	_delay_ms(10);
	
	//Invert the state after being inverted twice
	button_state = !button_state;
}

void Relay::button_set(int input)
{
	input = !!input; //Normalize the input to 1 or 0
	if(input != button_state) press();
}
