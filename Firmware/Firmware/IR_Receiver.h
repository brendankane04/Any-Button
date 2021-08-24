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
		//It varies by remote, but this corresponds to the remote in the README
		static const char POWER = 0x45;
		static const char MODE  = 0x46;
		static const char MUTE  = 0x47;
		static const char PAUSE = 0x44;
		static const char REWND = 0x40;
		static const char FFWD  = 0x43;
		static const char EQ    = 0x07;
		static const char VOLDN = 0x15;
		static const char VOLUP = 0x09;
		static const char ZERO  = 0x16;
		static const char SWTCH = 0x19;
		static const char US_D  = 0x0D;
		static const char ONE   = 0x0C;
		static const char TWO   = 0x18;
		static const char THREE = 0x5E;
		static const char FOUR  = 0x08;
		static const char FIVE  = 0x1C;
		static const char SIX   = 0x5A;
		static const char SEVEN = 0x42;
		static const char EIGHT = 0x52;
		static const char NINE  = 0x4A;

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
		//Constructor. Connect the IR receiver to the physical 'pin' on the DIP package
		//the pin is NOT the PCINTX signal
		IR_Receiver(int pin);
		//Read in an IR command & address
		IR_cmd recv();
		//Poll the receiver for a command coming in. Returns an error if there's an error
		unsigned char listen();
}; //IR_Receiver

#endif //__IR_RECEIVER_H__
