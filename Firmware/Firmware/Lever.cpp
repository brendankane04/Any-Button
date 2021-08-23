/* 
* Lever.cpp
*
* Created: 7/28/2021 6:01:32 PM
* Author: brend
*/

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "Relay.h"
#include "Lever.h"

#define FALSE 0
#define TRUE  1

//variable delay macro, since the library function requires a constant
#define var_delay(duration) for(int i = 0; i < duration; i++) _delay_ms(1);

Lever::Lever(int pin, int period) : Relay(pin)
{
	this->period = period;
}

void Lever::press()
{
	set(FALSE);
	_delay_ms(10);
	set(TRUE);
	var_delay(period); //Variable button hold
	set(FALSE);
	_delay_ms(10);
	
	//Invert the state after being inverted twice
	button_state = !button_state;

} 

