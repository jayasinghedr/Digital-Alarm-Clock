/*
 * AlarmTimer_code.cpp
 *
 * Created: 15/05/2021 22:18:08
 * Author : User
 */ 

#define F_CPU	16000000UL
#define AlarmLED	PORTD2
#define SnoozeLED	PORTD3
#define StopBTN		PIND4
#define SnoozeBTN	PIND5

#include <avr/io.h>
#include <util/delay.h>
#include "ds1307.h"

ds1307 DS1307;


int main(void)
{
	DDRD = (1<<AlarmLED) | (1<<SnoozeLED); // sets the pins PD2 & PD3 as outputs
	//DDRB = (1<<PORTB6) | (1<<PORTB7);	// X1 and X2  16MHz crystal
	PORTD |= (1<<PORTD4) | (1<<PORTD5); // enable the internal pull ups for PD4 & PD4
	
	ds1307::rtc_t rtc;

	// Setting time to the RTC
	rtc.seconds =  0x55; //
	rtc.minute =  0x30;
	rtc.hour = 0x11;	//  20:17:00
	rtc.weekDay = 0x02;
	rtc.date = 0x01;
	rtc.month = 0x06;
	rtc.year = 0x21;	//27th May 2021
	
	DS1307.set_time(&rtc);
	
	
	// stores the values from seconds(00H), minutes(01H) & hour(02H) registers

	int min, hr;
	uint8_t min_bcd, hr_bcd;

	// Button state
	bool stop = false;	//STOP button state
	bool snooze = false;	//Snooze button state
	
	// Set the alarm
	int alarm_min = 31;
	int alarm_hr = 11;
	int snoozeTime = 1;	//set snooze to 1 min
	
	while (1)
	{
		//read current time from the RTC
		//sec = read_time(0x00);
		min_bcd = DS1307.read_time(0x01);	// Minutes from register 01H
		hr_bcd = DS1307.read_time(0x02);	// Hours from register 02H
		
		min = DS1307.bcd_to_dec(min_bcd);	//convert minutes to decimal form
		hr = DS1307.bcd_to_dec(hr_bcd);	//convert hours to decimal form

		//------------Alarm ON-----------------------------------------------------------------
		
		if ((min == alarm_min)  & (hr == alarm_hr) & ~(stop)){
			// if the current time == alarm time & StopBTN is off-> switch ON Alarm LED
			PORTD |= (1<<AlarmLED);
		}
		
		else{
			// after 1 min or when StopBTN is already pressed -> switch OFF AlarmLED
			PORTD &= ~(1<<AlarmLED);
		}
		
		
		//-------------Alarm Stop-------------------------------------------------------------
		
		if (!(PIND & (1<<StopBTN)) & !(~PORTD & (1<<AlarmLED))){
			//if AlarmLED is ON & StopBTN is pressed -> switch off AlarmLED
			PORTD &= ~(1<<AlarmLED);
			stop = true;	// state of stop button set to true
		}
		
		
		//------------Alarm Snooze------------------------------------------------------------
		
		if (!(PIND & (1<<SnoozeBTN)) & !(~PORTD & (1<<AlarmLED))){
			// To indicate the SnoozeBTN was pressed SnoozeLED lights up for 0.5s
			PORTD |= (1<<SnoozeLED);
			_delay_ms(500);
			PORTD &= ~(1<<SnoozeLED);
			PORTD &= ~(1<<AlarmLED);	// AlarmLED switches OFF
			snooze = true;				//state of SnoozeBTN set to 1
		}
		
		if (snooze){
			// extends the alarm time after the SnoozeBTN is pressed
			if (alarm_min == 59){
				alarm_min = 0;
				if (alarm_hr == 23){
					alarm_hr = 0;
				}
				else{
					alarm_hr += 1;
				}
			}
			else{
				alarm_min += snoozeTime;
			}
			PORTD |= (1<<PORTD5);	//Sets the SnoozeBTN to high (internal pull up)
			snooze = false;
		}
	}
}



