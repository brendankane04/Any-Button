//Remote Control Receiver Momentary+Alternate Original ATtiny13A 20191021 2200
//PB1,PB2 : Momentary Operation
//PB3,PB4 : Alternate Operation

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define pin PINB

uint16_t cti;
uint8_t ir=0x01,ib,bt,custom,data;

void infrared(){

	cti=0;while(~pin & ir){cti++;_delay_us(100);} //Leader(16T) Check
	if(cti>70 && cti<100){ //cti:90(16T)

		cti=0;while((pin & ir)&&(cti<55)){cti++;_delay_us(100);} //Blank(8T) Check

		if(cti>35){ //cti:45(8T)
			for(ib=0;ib<16;ib++){
				while(~pin & ir);
				cti=0;while((pin & ir)&&(cti<20)){cti++;_delay_us(100);}
				if(cti>10){bt=1;}else{bt=0;} //cti:16(3T)
				data<<=1; //data:Data Code
				data|=bt;
				if(ib==7){custom=data;data=0;} //custom:Custom Code
			}
			if(custom==0x99){
				if(data==0x01){PORTB|=(1<<1);} //PB1:Momentary
				if(data==0x02){PORTB|=(1<<2);} //PB2:Momentary
				if(data==0x03){PORTB^=(1<<3);} //PB3:Alternate
				if(data==0x04){PORTB^=(1<<4);} //PB4:Alternate

				cti=0;while((pin & ir)&&(cti<10)){cti++;_delay_us(100);}
				while(~pin & ir); //Stop Bit
			}
		}//if(cti>35
		
	}//if(cti>70

	cti=0;
	for(;;){ //Blank Check
		cti++;
		_delay_us(100);
		if(~pin & ir){cti=0;}
		if(cti>500){PORTB&=0b11111001;break;}
	}
}

int main( void ){

	CLKPR =0b10000000; //Prescaler Change Enable
	CLKPR =0b00000000; //Div1(9.6MHz)

	DDRB  =0b00011110; //PB4-1:LED
	PORTB =0b00000000; //PB0:IR Sensor

	while(1){

		if(~pin & ir){infrared();}

	}
}