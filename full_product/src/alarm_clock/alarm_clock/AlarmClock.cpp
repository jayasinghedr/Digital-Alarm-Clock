/*
 * AlarmClock.cpp
 *
 * Created: 16/06/2021 20:28:44
 *  Author: User
 */ 

 #define F_CPU 8000000L
 #include <avr/io.h>
 #include <util/delay.h>
 #include "ds1307.h"
 #include "LCD_Display.h"
 #include "AlarmClock.h"
 #include "Get_key.h"
 
 #define Up		PINC0
 #define Down	PINC1
 #define Ok		PINC2
 #define Back	PINC3
 
 ds1307 ds1307_1;
 LCD_Display lcd_1;
 Get_key keypad_1;

 char* AlarmClock::int_to_char(int num){
	 int temp, div, rem, x;
	 char* chArr;
	 if (num > 9){
		 chArr = "__";
		 x = num / 10;
		 div = x + 48;
		 rem = (num % (10 * x)) + 48;
		 char ch1 = div;
		 char ch2 = rem;
		 chArr[0] = ch1;
		 chArr[1] = ch2;
	 }
	 else{
		 chArr = "0_";
		 temp = num + 48;
		 char ch = temp;
		 chArr[1] = ch;
	 }
	 return chArr;
 }

 void AlarmClock::displayTime(){

	 //read current time from RTC
	 char* str_sec;
	 char* str_min;
	 char* str_hr;

	 char* time1 = "    00:00:00     ";
	 int sec, min, hr;
	 //uint8_t sec_bcd, min_bcd, hr_bcd;

	 sec = ds1307_1.read_time(0x00);	//read from seconds reg
	 min = ds1307_1.read_time(0x01);	//read from minutes reg
	 hr = ds1307_1.read_time(0x02);		//read from hours reg
	 
	 str_hr = int_to_char(hr);
	 time1[4] = str_hr[0];
	 time1[5] = str_hr[1];
	 
	 str_min = int_to_char(min);
	 time1[7] = str_min[0];
	 time1[8] = str_min[1];
	 
	 str_sec = int_to_char(sec);
	 time1[10] = str_sec[0];
	 time1[11] = str_sec[1];
	 
	 lcd_1.LCD_String_xy(0, 0, time1);       //Write string on 1st line of LCD
	 lcd_1.LCD_String_xy(1, 0, "MENU            ");		//Write string on 2nd line
	 _delay_ms(1000);
}

 void AlarmClock::setTimetoRTC(){
	
	ds1307::rtc_t rtc;
	uint8_t hour, seconds, minutes, key;
	char* time = "00:00:00";
	int sec, min, hr;
	sec=0;
	min=0;
	hr=0;
	int n[6] = {4, 5, 7, 8, 10, 11};
	lcd_1.LCD_Clear();
	lcd_1.LCD_String_xy(0, 4, time);
	_delay_ms(500);

	for(uint8_t i=0;i<7;i++)
	{
		while(1)
		{
			key = keypad_1.GetKey();
			if (key == 1) {lcd_1.LCD_String_xy(0,n[i],"1");break;}
			if (key == 2) {lcd_1.LCD_String_xy(0,n[i],"2");break;}
			if (key == 3) {lcd_1.LCD_String_xy(0,n[i],"3");break;}
			if (key == 4) {lcd_1.LCD_String_xy(0,n[i],"4");break;}
			if (key == 5) {lcd_1.LCD_String_xy(0,n[i],"5");break;}
			if (key == 6) {lcd_1.LCD_String_xy(0,n[i],"6");break;}
			if (key == 7) {lcd_1.LCD_String_xy(0,n[i],"7");break;}
			if (key == 8) {lcd_1.LCD_String_xy(0,n[i],"8");break;}
			if (key == 9) {lcd_1.LCD_String_xy(0,n[i],"9");break;}
			if (key == 11) {lcd_1.LCD_String_xy(0,n[i],"0");key=0;break;}
			//if (key == 10) {lcd.LCD_String_xy(0,n[i],"P");break;}
			if (PINC & (1<<Ok)){i=8; break;}
			//if (i == 6){i = 0;}
		}

		if (i == 0){hr+=key*10;}
		if (i == 1){hr+=key;}
		if (i == 2){min+=key*10;}
		if (i == 3){min+=key;}
		if (i == 4){sec+=key*10;}
		if (i == 5){sec+=key;}

	}
	
	hour = ds1307_1.dec_to_bcd(hr);
	minutes = ds1307_1.dec_to_bcd(min);
	seconds = ds1307_1.dec_to_bcd(sec);

	// Setting time to the RTC
	rtc.seconds =  seconds;
	rtc.minute =  minutes;
	rtc.hour = hour;
	rtc.weekDay = 0x07;
	rtc.date = 0x20;
	rtc.month = 0x06;
	rtc.year = 0x21;
	lcd_1.LCD_Clear();
	ds1307_1.set_time(&rtc);
	lcd_1.LCD_String_xy(0, 4, "Time Set");
	lcd_1.LCD_String_xy(1, 0, "OK");
	//_delay_ms(500);
	//lcd_1.LCD_Clear();
 }

 int* AlarmClock::setNewAlarm(){
	uint8_t key;
	char* alarmTime = "00:00";
	int min_al=0, hr_al=0;
	int n[6] = {6, 7, 9, 10};
	static int alarm[2];
			
	lcd_1.LCD_Clear();
	lcd_1.LCD_String_xy(0, 6, alarmTime);
	_delay_ms(200);	
	for(uint8_t i=0;i<5;i++)
	{
		while(1)
		{
			key = keypad_1.GetKey();
			if (key == 1) {lcd_1.LCD_String_xy(0,n[i],"1");break;}
			if (key == 2) {lcd_1.LCD_String_xy(0,n[i],"2");break;}
			if (key == 3) {lcd_1.LCD_String_xy(0,n[i],"3");break;}
			if (key == 4) {lcd_1.LCD_String_xy(0,n[i],"4");break;}
			if (key == 5) {lcd_1.LCD_String_xy(0,n[i],"5");break;}
			if (key == 6) {lcd_1.LCD_String_xy(0,n[i],"6");break;}
			if (key == 7) {lcd_1.LCD_String_xy(0,n[i],"7");break;}
			if (key == 8) {lcd_1.LCD_String_xy(0,n[i],"8");break;}
			if (key == 9) {lcd_1.LCD_String_xy(0,n[i],"9");break;}
			if (key == 11) {lcd_1.LCD_String_xy(0,n[i],"0");key=0;break;}
			if (PINC & (1<<Ok)){i=8; break;}
			//if (key == 10) {lcd.LCD_String_xy(0,n[i],"P");break;}
		}

		if (i == 0){hr_al+=key*10;}
		if (i == 1){hr_al+=key;}
		if (i == 2){min_al+=key*10;}
		if (i == 3){min_al+=key;}	
		
	}
	alarm[0] = hr_al;
	alarm[1] = min_al;
	return alarm;
 }

