/* 
* Lever.h
*
* Created: 7/28/2021 6:01:34 PM
* Author: brend
*/


#ifndef __LEVER_H__
#define __LEVER_H__


//Controls a relay connected to a lever
class Lever : public Relay
{

private:	
	int period; //The length of the the button press in milliseconds

public:
	//Default Constructor
	Lever();
	//Constructor 
	Lever(int pin, int period);
	//Modified button press function. It holds for a longer, variable time based on the solenoid
	void press();
}; //Lever

#endif //__LEVER_H__
