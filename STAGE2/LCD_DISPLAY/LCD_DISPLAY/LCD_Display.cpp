/*
 * LCD_Display.cpp
 *
 * Created: 21/05/2021 11:29:45 PM
 *  Author: Jayabawan
 */ 

#define F_CPU 8000000L	
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_Display.h"


#define LCD_Dir_00    DDRB									   //assigning the values to the defined variables
#define LCDER_port    PORTB
#define Rsel          PB0
#define ENable        PB1


void LCD_Display::LCD_Commandgiver( unsigned char comand)      //function to give commands to the LCD
{
	LCDER_port=(LCDER_port & 0x0F) | (comand & 0xF0);          //Sending upper nibble
	LCDER_port &= ~ (1<<Rsel);							       //setting the pin0 of portB LOW to write
	LCDER_port |= (1<<ENable);                                 //setting the pin1 of portB HIGH to read
	_delay_us(2);
	LCDER_port &= ~ (1<<ENable);						       //setting the pin1 of portB LOW to write
	
	_delay_us(200);
	
	LCDER_port = (LCDER_port & 0x0F) | (comand << 4);          //Sending lower nibble
	LCDER_port |= (1 << ENable);                               //setting the pin1 of portB HIGH to read
	_delay_us(2);
	LCDER_port &= ~(1<< ENable);                               //setting the pin1 of portB LOW to write
	_delay_ms(2);
}

void LCD_Display::LCD_Initializer(){                           // function to output signal towards LCD
	LCD_Dir_00 = 0xFF;                                         // setting the portB to be in Output mode
	_delay_ms(20);
	
	LCD_Commandgiver(0x02);                                    //initializes LCD 16x2 in 4-bit mode
	LCD_Commandgiver(0x28);                                    // configures LCD in 2-line, 4-bit mode, and 5x8 dots.
	LCD_Commandgiver(0x0c);                                    //Send any Display ON command
	LCD_Commandgiver(0x06);                                    //increment cursor)
	LCD_Commandgiver(0x01);                                    //Clear display screen
	_delay_ms(2);
}

void LCD_Display::LCD_Character( unsigned char data_00)        //function to output characters towards LCD
{
	LCDER_port = ( LCDER_port & 0x0F) | (data_00 & 0xF0 );     //Sending upper nibble
	LCDER_port |= (1<<Rsel);                                   //setting the pin0 of portB HIGH to read
	LCDER_port |=(1<<ENable);                                  //setting the pin1 of portB HIGH to read
	_delay_us(1);
	LCDER_port &= ~(1<<ENable);                                //setting the pin1 of portB LOW to write
	
	_delay_us(200);
	
	
	LCDER_port = ( LCDER_port & 0x0F) | (data_00 <<4 );        //Sending lower nibble
	LCDER_port |= (1<< ENable);                                //setting the pin1 of portB HIGH to read
	_delay_us(1);
	LCDER_port &= ~(1<<ENable);                                //setting the pin1 of portB LOW to write
	_delay_ms(2);
}

void LCD_Display::LCD_String(char *string_00)                  //function to output the set of characters as a string
{
	for (int ci=0;string_00[ci] != 0; ci++)                    //for loop to accumulate characters to create string
	{
		LCD_Character (string_00[ci]);                         //calling the above defined function to create the string using characters
	}
}

void LCD_Display::LCD_Clear()                                  //function to clear the LCD after displaying the output
{
	LCD_Commandgiver(0x01);                                    //Clear display screen
	_delay_ms(2);
	LCD_Commandgiver(0x80);                                    //Cursor at home position
}

void LCD_Display::LCD_String_xy(char row_1, char position, char *string_00) //function to set the position of the LCD cursor
{
	if (row_1 == 0 && position<16)
	LCD_Commandgiver((position & 0x0F)| 0x80);                 //Command of first row and required position<16
	else if (row_1 == 1 && position<16)
	LCD_Commandgiver((position &0x0F) | 0xC0);                 //Command of first row and required position<16
	LCD_String(string_00);                                     //calling the above defined function
}