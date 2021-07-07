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


void Write(char);

//Class which reads the input of an IR receiver on the INT0 pin
class IR_Receiver
{
	private:
		//Constants for reading in the IR command 
		static const int AGC_PULSE = 7500;
		static const int LONG_PULSE = 3000;
		static const int ONE_PULSE = 1200;

		//waits until the interrupt pin is triggered to continue and records how long the device waited for a response in microseconds
		int wait_until_change()
		{
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

		//Record the length of 1 pulse of a square wave in microseconds
		int measure_square_wave()
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
			length = measure_square_wave();
			if(length < ONE_PULSE)
				return 0x00;
			else
				return 0x01;
		}

		//Read in a byte from LSB to MSB
		char read_byte()
		{
			char output = 0x00;
			for(int i = 0; i < 8; i++)
				output |= read_bit() << i;

			return output;
		}

	public:
		//Constants which define the command numbers
		static const char POWER = 0x45;
		static const char ZERO  = 0x16;
		static const char ONE   = 0x0C;

		struct IR_cmd
		{
			unsigned char addr;
			unsigned char cmd;
		};

		//Constructor
		IR_Receiver()
		{
			//Set up the interrupt on the INT0 pin to receive the IR signal
			//Initialize the interrupt mode for INT0
			MCUCR |= _BV(ISC00); 
		}

		//Read in an IR command & address
		IR_cmd recv()
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
				output.cmd = 0;
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
			wait_until_change();

			//Check for error conditions regarding the inverted bits
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
};

//Class which controls a relay for toggle & setting configuration
class Relay
{
	private:
		int state;
		int pin;

	public:
		//Default Constructor
		Relay()
		{
			Relay(1);
		}

		//pin: which pin on PORTB the relay is connected to
		Relay(int pin)
		{
			//Initialize the state as off
			state = 0;

			//Ensure the pin is one of the 5 possibilities & set the pin for this relay
			if(0 <= pin && pin <= 5) 
				this->pin = pin;
			else
				this->pin = 1; //1 is the default pin

			//Set the pin as an output
			DDRB |= _BV(pin);
		}	

		void toggle()
		{
			if(state)
				PORTB &= ~_BV(pin);
			else
				PORTB |= _BV(pin);

			state = !state;
		}

		void set(int input)
		{
			input = !!input; //Normalize the input to 1 or 0
			if(input != state) toggle(); //Toggle the pin if the goal & current setting are different
		}
};

//Initialize the bit-bang write command
void Write_init()
{
	//Set the SDA & SCL pins as outputs
	DDRB |= SDA | SCL;
}

//VERY Rudimentary bit-banged I2C function for debugging
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

int main(void)
{
	Write_init();

	IR_Receiver sensor1;
	Relay relay1(1);

	//Initialize an empty IR command
	IR_Receiver::IR_cmd remote_cmd;
	remote_cmd.addr = 0x00;
	remote_cmd.cmd = 0x00;

	sei();

	while(1)
	{
		remote_cmd = sensor1.recv();
		switch(remote_cmd.cmd)
		{
			case IR_Receiver::POWER:
				relay1.toggle();
				break;
			case IR_Receiver::ZERO:
				relay1.set(FALSE);
				break;
			case IR_Receiver::ONE:
				relay1.set(TRUE);
				break;
			default:
				break;
		}
	}
}
