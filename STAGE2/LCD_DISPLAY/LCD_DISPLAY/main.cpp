/*
 * LCD_DISPLAY.cpp
 *
 * Created: 21/05/2021 1:32:32 AM
 * Author : Jayabawan
 */ 

#define F_CPU 8000000L										   //defining the speed of the clock
#include <avr/io.h>										       //including input/output pin library
#include <util/delay.h>									       //including delay library 
#include "LCD_Display.h"   
LCD_Display lcd;
                      
int main(void)
{
	lcd.LCD_Initializer();                                     //Initialization of LCD
	DDRD = 0x07;                                               //0x07=0b00000111 set d0,d1,d2 as output pins(LED"s are connected)
	PORTD=0x38;                                                //0x38=0b00111000 set d3,d4,d5 as high so it can read the value(button's)
	
    while (1) 
	
	{
		if(!(PIND & 0x08))                                     //checks whether the button of d3 is pressed
		{
			PORTD |= 0x01;                                     //0x01=0b00000001, make d0 as high
			lcd.LCD_String("YOU HAVE PRESSED");                //Write string on 1st line of LCD
			lcd.LCD_Commandgiver(0xC0);                        //Go to 2nd line
			lcd.LCD_String("THE RED BUTTON");                  //Write string on 2nd line
			_delay_ms(1000);
			lcd.LCD_Clear();
		}
		else
		{
			PORTD &= 0xFE;                                     //make d0 as low
		}
		
		if(!(PIND & 0x10))                                     //checks whether the button of d4 is pressed
		{
			PORTD |= 0x02;                                     //0x02=0b00000010, make d1 as high
			lcd.LCD_String("YOU HAVE PRESSED");                //Write string on 1st line of LCD
			lcd.LCD_Commandgiver(0xC0);                        //Go to 2nd line
			lcd.LCD_String("THE BLUE BUTTON");                 //Write string on 2nd line
			_delay_ms(1000);
			lcd.LCD_Clear();
		}
		else
		{
			PORTD &= 0xFD;                                     //make d1 as low
		}
		
		if(!(PIND & 0x20))                                     //checks whether the button of d5 is pressed
		{
			PORTD |= 0x04;                                     //0x04=0b00000100, make d2 as high
			lcd.LCD_String("YOU HAVE PRESSED");                //Write string on 1st line of LCD
			lcd.LCD_Commandgiver(0xC0);                        //Go to 2nd line
			lcd.LCD_String("THE GREEN BUTTON");                //Write string on 2nd line
			_delay_ms(1000);
			lcd.LCD_Clear();
		}
		else
		{
			PORTD &= 0xFB;                                      //make d2 as low
		}
	}
}



