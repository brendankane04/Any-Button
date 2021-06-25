/*
 * NEC Protocol IR remote control decoder using PIC16F877A CCS C code
 * Firmware.cpp
 *
 * Created: 6/9/2021 4:39:57 PM
 * Author : brend
 */ 

using namespace std;

#ifndef F_CPU 
#define F_CPU 1600000UL //1.6MHz
#endif

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define TRUE 1
#define FALSE 0

#define PIN(pin) (1 << (pin)) //Pick a specific pin on a port

uint32_t ir_code = 0;
uint16_t address = 0;
uint8_t command = 0;
uint8_t inv_command = 0;

//Reads in the input of one pin
int input(int pin)
{
	return PORTB & PIN(pin);
}

//Reads in the NEC code of an IR receiver
short nec_remote_read()
{
	uint8_t count = 0, i = 0;

	// Check 9ms pulse (remote control sends logic high)
	while((input(0) == 0) && (count < 200))
	{
		count++;
		_delay_us(50);
	}

	if( (count > 199) || (count < 160))        // NEC protocol?
		return FALSE;

	count = 0;
	// Check 4.5ms space (remote control sends logic low)
	while((input(0)) && (count < 100))
	{
		count++;
		_delay_us(50);
	}

	if( (count > 99) || (count < 60))          // NEC protocol?
		return FALSE;

	// Read code message (32-bit)
	for(i = 0; i < 32; i++)
	{
		count = 0;
		while((input(0) == 0) && (count < 14))
		{
			count++;
			_delay_us(50);
		}

		if( (count > 13) || (count < 8))      // NEC protocol?
			return FALSE;

		count = 0;
		while((input(0)) && (count < 40))
		{
			count++;
			_delay_us(50);
		}

		if( (count > 39) || (count < 8))      // NEC protocol?
			return FALSE;

		if( count > 20)                       // If space width > 1ms
			//bit_set(ir_code, (31 - i));         // Write 1 to bit (31 - i)
			ir_code |= (1 << (31 - i));
		else                                  // If space width < 1ms
			//bit_clear(ir_code, (31 - i));       // Write 0 to bit (31 - i)
			ir_code &= ~(1 << (31 - i));
	}
	return TRUE;
}

int main(void)
{
	DDRB |= PIN(2);
    while (1) 
    {
		PORTB |= PIN(2);
		_delay_ms(100);
		PORTB &= ~PIN(2);
		_delay_ms(100);
    }
}

