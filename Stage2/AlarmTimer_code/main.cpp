/*
 * AlarmTimer_code.cpp
 *
 * Created: 15/05/2021 22:18:08
 * Author : User
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "ds1307.h"


int main(void)
{
	DDRD = (1<<PORTD2) | (1<<PORTD3); // sets the pins PD2 & PD3 as outputs
	PORTD |= (1<<PORTD4) | (1<<PORTD5); // enable the input pull ups for PD4 & PD4
	
	rtc_t rtc;
	
	rtc.seconds =  0x55;
	rtc.minute =  0x00;
	rtc.hour = 0x20; //  20:17:00

	rtc.weekDay = 0x04;
	rtc.date = 0x27;
	rtc.month = 0x05;
	rtc.year = 0x21; //27th May 2021
	
	set_time(&rtc);
	
	uint8_t sec;
	uint8_t min;
	uint8_t hr;
	bool off = false;
	bool snooze = false;
	
	
	uint8_t alarm_min = 0x01;
	uint8_t alarm_hr = 0x20;
	
	while (1)
	{
		//read current time from the RTC
		sec = read_time(0x00);
		min = read_time(0x01);
		hr = read_time(0x02);
		
		
		if (min == alarm_min  & hr == alarm_hr & ~(off)){
			
			PORTD |= (1<<PORTD2);
		}
		
		else{
			PORTD &= ~(1<<PORTD2);
		}
		
		
		//Alarm Stop button
		//STOP button is pressed and the Alarm is going
		if (!(PIND & (1<<PIND4)) & !(~PORTD & (1<<PORTD2))){
			PORTD &= ~(1<<PORTD2);
			off = true;
			
		}
		
		//Alarm Snooze button
		if (!(PIND & (1<<PIND5))){
			PORTD |= (1<<PORTD3);
			_delay_ms(500);
			PORTD &= ~(1<<PORTD3);
			snooze = true;
		}
		
		if (snooze){
			alarm_min++;
			PORTD &= ~(1<<PORTD2);
			PORTD |= (1<<PORTD5);
			snooze = false;
		}
		
	}
}


