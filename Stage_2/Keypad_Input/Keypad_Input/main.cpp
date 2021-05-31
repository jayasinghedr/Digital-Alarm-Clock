/*
 * Keypad_Input.cpp
 *
 * Created: 5/21/2021 7:21:13 PM
 * Author : User
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "Get_key.h"

Get_key keypad;

int main(void)
{
    /* Replace with your application code */
    uint8_t key;
    DDRB = 0b00000001;
    while (1)
    {
	    key = keypad.GetKey();
	    
	    
	    if (key < 13) {for (uint8_t i = 0;i<key;i++){PORTB = 0b00000001;_delay_ms(100);PORTB = 0b00000000;_delay_ms(100);}}
	}
	    
}

