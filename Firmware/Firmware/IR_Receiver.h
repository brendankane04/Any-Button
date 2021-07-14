/* 
* IR_Receiver.h
*
* Created: 7/7/2021 6:06:22 PM
* Author: brend
*/


#ifndef __IR_RECEIVER_H__
#define __IR_RECEIVER_H__

//Class which reads the input of an IR receiver on the INT0 pin
class IR_Receiver
{
	private:
		//Constants for reading in the IR command 
		static const int AGC_PULSE  = 7500;
		static const int LONG_PULSE = 3000;
		static const int ONE_PULSE  = 1200;
		
	public:
		//Constants which define the command numbers
		//It varies by remote
		static const char POWER = 0x45;
		static const char ZERO  = 0x16;
		static const char ONE   = 0x0C;

		struct IR_cmd
		{
			unsigned char addr;
			unsigned char cmd;
		};

	private:
		//waits until the interrupt pin is triggered to continue and records how long the device waited for a response in microseconds
		int wait_until_change();
		//Record the length of 1 pulse of a square wave in microseconds
		int measure_square_wave();
		//Read in a single bit of the IR code based on the length of the square wave
		char read_bit();
		//Read in a byte from LSB to MSB
		char read_byte();
		
	public:
		//Default Constructor
		IR_Receiver();
		//Constructor. Connect the IR receiver to the physical 'pin' on the DIP package
		//the pin is NOT the PCINTX signal
		IR_Receiver(int pin);
		//Read in an IR command & address
		IR_cmd recv();
}; //IR_Receiver

#endif //__IR_RECEIVER_H__
