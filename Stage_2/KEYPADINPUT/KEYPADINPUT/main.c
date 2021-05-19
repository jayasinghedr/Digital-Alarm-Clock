/*
 * KEYPADINPUT.c
 *
 * Created: 5/18/2021 7:33:56 AM
 * Author : User
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL
uint8_t GetKey()
{
	uint8_t r,c;
	PORTD |= 0b00001111;
	
	for (c=0;c<3;c++)
	{
		DDRD &=~(0b01111111);
		DDRD |=(0b01000000>>c);
		for (r=0;r<4;r++)
		{
			if(!(PIND & (0b00001000>>r)))
			{
				while(!(PIND & (0b00001000>>r)));
				return(r*3+c +1);
			}
		}
	}
	
	return 0xFF;
}


int main(void)
{
    /* Replace with your application code */
	uint8_t key;
	DDRB = 0b00000001;
    while (1) 
    {
		key = GetKey();
		
	
		if (key < 13) {for (uint8_t i = 0;i<key;i++){_delay_ms(100);PORTB = 0b00000001;_delay_ms(100);PORTB = 0b00000000;}}
		
	    
		
		
		
    }
}

