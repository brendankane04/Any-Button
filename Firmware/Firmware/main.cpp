//Remote Control Receiver Momentary+Alternate Original ATtiny13A 20191021 2200
//PB1,PB2 : Momentary Operation
//PB3,PB4 : Alternate Operation

#ifndef F_CPU
#define F_CPU 8000000UL
#endif 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "IR_Receiver.h"
#include "Relay.h"
#include "BB_I2C.h"

#define FALSE 0
#define TRUE  1

int main(void)
{
	IR_Receiver sensor1;
	Relay relay1;
	BB_I2C writer(4, 3);

	//Initialize an empty IR command
	IR_Receiver::IR_cmd remote_cmd;

	while(1)
	{
		remote_cmd = sensor1.recv();
		switch(remote_cmd.cmd)
		{
			case IR_Receiver::POWER:
				relay1.press();
				break;
			case IR_Receiver::ZERO:
				relay1.button_set(FALSE);
				break;
			case IR_Receiver::ONE:
				relay1.button_set(TRUE);
				break;
			default:
				break;
		}
	}
}
