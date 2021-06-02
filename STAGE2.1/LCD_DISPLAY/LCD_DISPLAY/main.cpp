/*
 * LCD_DISPLAY.cpp
 *
 * Created: 21/05/2021 1:32:32 AM
 * Author : Jayabawan
 */ 

#define F_CPU 8000000L										   //defining the speed of the clock
#include <avr/io.h>										       //including input/output pin library
#include <util/delay.h>									       //including delay library 
#include "LCD_Display.h"                                       //including the library of set of  lcd functions
LCD_Display lcd;                                               //calling the Classes of the objects
                      
int main(void)
{
	lcd.LCD_Initializer();                                     //Initialization of LCD
	DDRB = 0x07;                                               //0x07=0b00000111 set PB0,PB1,PB2 as output pins(LED"s are connected)
	PORTB=0x38;                                                //0x38=0b00111000 set PB3,PB4,PB5 as high so it can read the value(button's)
	
    while (1) 
	
	{
		if(!(PINB & 0x08))                                     //checks whether the button of PB3 is pressed
		{
			PORTB |= 0x01;                                     //0x01=0b00000001, make PB0 as high, LED lights up
			lcd.LCD_String("YOU HAVE PRESSED");                //Write string on 1st line of LCD
			lcd.LCD_Commandgiver(0xC0);                        //Go to 2nd line
			lcd.LCD_String("THE RED BUTTON");                  //Write string on 2nd line
			_delay_ms(1000);
			lcd.LCD_Clear();
		}
		else
		{
			PORTB &= 0xFE;                                     //make PB0 as low,LED lights off
		}
		
		if(!(PINB & 0x10))                                     //checks whether the button of PB4 is pressed
		{
			PORTB |= 0x02;                                     //0x02=0b00000010, make PB1 as high,LED lights up
			lcd.LCD_String("YOU HAVE PRESSED");                //Write string on 1st line of LCD
			lcd.LCD_Commandgiver(0xC0);                        //Go to 2nd line
			lcd.LCD_String("THE BLUE BUTTON");                 //Write string on 2nd line
			_delay_ms(1000);
			lcd.LCD_Clear();
		}
		else
		{
			PORTB &= 0xFD;                                     //make PB1 as low,LED lights off
		}
		
		if(!(PINB & 0x20))                                     //checks whether the button of d5 is pressed
		{
			PORTB |= 0x04;                                     //0x04=0b00000100, make PB2 as high, led lights up
			lcd.LCD_String("YOU HAVE PRESSED");                //Write string on 1st line of LCD
			lcd.LCD_Commandgiver(0xC0);                        //Go to 2nd line
			lcd.LCD_String("THE GREEN BUTTON");                //Write string on 2nd line
			_delay_ms(1000);
			lcd.LCD_Clear();
		}
		else
		{
			PORTB &= 0xFB;                                      //make PB2 as low,LED lights off
		}
	}
}



