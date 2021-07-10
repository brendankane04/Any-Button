/* 
* BB_I2C.h
*
* Created: 7/7/2021 11:03:41 PM
* Author: brend
*/


#ifndef __BB_I2C_H__
#define __BB_I2C_H__


//Class which controls a bit-bang I2C-like protocol for writing bytes out for debugging
//It's VERY rudimentary
class BB_I2C
{
	private:
		//pins on the PORTB line which correspond to the SDA & SCL pins
		char SDA;
		char SCL;
	
	public:
		//Constructor
		BB_I2C(int sda, int scl);
		//Rudimentary bit-banged I2C function for debugging
		void write(char data);
};

#endif //__BB_I2C_H__
