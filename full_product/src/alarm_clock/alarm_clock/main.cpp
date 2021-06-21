/*
 * alarm_clock.cpp
 *
 * Created: 04/06/2021 23:16:13
 * Author : User
 */ 

#define F_CPU 8000000L										   //defining the speed of the clock
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__									       //including input/output pin library
#include <util/delay.h>									       //including delay library
#include "LCD_Display.h"
#include "AlarmClock.h"
#include "music_notations.h"
#include "ds1307.h"
#include "Get_key.h"
#include "menu.h"

 ds1307 DS1307;
 LCD_Display lcd;
 Get_key keypad;
 AlarmClock alarmclock;
 menu MENU;

int main(void)
{
	lcd.LCD_Initializer();                                     //alization Initiof LCD
	/*ds1307::rtc_t rtc;	// Setting time to the RTC	rtc.seconds =  0x50; //	rtc.minute =  0x00;	rtc.hour = 0x12;	//  20:17:00	rtc.weekDay = 0x05;	rtc.date = 0x31;	rtc.month = 0x05;	rtc.year = 0x21;	//27th May 2021		DS1307.set_time(&rtc);*/
                                               //0x38=0b00111000 set d3,d4,d5 as high so it can read the value(button's)
	MENU.display();
	//lcd.LCD_String();
	while (1)
	{
		
		MENU.okbtn();
		MENU.upbtn();
		MENU.dwnbtn();
		MENU.backbtn();
		
		
		
		
		
		
		
	}
}



