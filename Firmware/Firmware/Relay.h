/* 
* Relay.h
*
* Created: 7/7/2021 11:03:30 PM
* Author: brend
*/

#ifndef __RELAY_H__
#define __RELAY_H__

//Class which controls a relay for toggle & setting configuration
class Relay
{
	private:
		int state;
		int button_state;
		int pin;

	//Set the external device to LOW, whatever that means
	void Deactivate();
	//Set the external device to HIGH, whatever that means
	void Activate();

	public:
		//Default Constructor
		Relay();
		//pin: which pin on PORTB the relay is connected to
		Relay(int pin);
		//Change the relay's current state
		void toggle();
		//Set the relay to the target 'input'
		void set(int input);
		//Toggle a button which must be held down, then released
		void press();
		//Set the status of a device but for a button
		void button_set(int input);
};

#endif //__RELAY_H__
