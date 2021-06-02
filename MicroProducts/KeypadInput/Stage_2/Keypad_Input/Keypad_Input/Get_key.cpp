/*
 * Get_key.cpp
 *
 * Created: 5/21/2021 8:11:33 PM
 *  Author: User
 */ 
#include <avr/io.h>
#include "Get_key.h"


uint8_t Get_key::GetKey()

{
	uint8_t r,c;
	PORTD |= 0b00001111;
	
	for (c=0;c<3;c++)//identifying the column of the pressed key
	{
		DDRD &=~(0b01111111);
		DDRD |=(0b01000000>>c);
		for (r=0;r<4;r++)//identifying the row of the pressed key
		{
			if(!(PIND & (0b00001000>>r)))
			{
				while(!(PIND & (0b00001000>>r)));
				return(r*3+c +1);// returning the pressed number by considering the row and the column pressed
			}
		}
	}
	
	return 0xFF;
}