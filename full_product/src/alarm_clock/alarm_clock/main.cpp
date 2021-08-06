/*
 * alarm_clock.cpp
 *
 * Created: 04/06/2021 23:16:13
 * Author : User
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "ds1307.h"
#include "LCD_Display.h"
#include "Get_key.h"
#include "AlarmClock.h"
#include "music_notations.h"

#define Up		PINC0
#define Down	PINC1
#define Ok		PINC2
#define Back	PINC3

void display();
void okbtn();
void upbtn();
void backbtn();
void dwnbtn();
void checkAlarm();
void changeAlarm(int alPos);

ds1307 DS1307;
LCD_Display lcd;
Get_key keypad;
AlarmClock alarmclock;
music_notations music;

int set = 0;
const int numofscreens1 = 5;
int currentscreenset1 = 0;
const int numofscreens20 = 1;
int currentscreenset20 = 0;
const int numofscreens21 = 5;
int currentscreenset21 = 0;
const int numofscreens22 = 1;
int currentscreenset22 = 0;
const int numofscreens23 = 5;
int currentscreenset23 = 0;
const int numofscreens24 = 1;
int currentscreenset24 = 0;

char Menu[5][2][16] = {
	{"New Alarm","OK         BACK"},
	{"All Alarms","OK         BACK"},
	{"Set Time","OK         BACK"},
	{"Alarm Tone","OK         BACK"},
	{"Reset","OK         BACK"}
};

char allAlarmsMenu[5][16] = {"Alarm1 OFF", "Alarm2 OFF", "Alarm3 OFF", "Alarm4 OFF","Alarm5 OFF"};

char alarmChangeList[5][16] = {"00:00", "00:00", "00:00", "00:00", "00:00"};

char alarmtone[5][2][16] = {
	{"GOT","OK             "},
	{"PIRATES","OK             "},
	{"STARWARS","OK             "},
	{"ASTRONOMIA","OK             "},
	{"TAKE IN ME","OK             "}
};

char reset[][16] = {"reset all"};

int allAlarms[5][4];	//saves all the alarms in int values [Alarm Hr, AlarmMin, 1/0, ON/OFF]

int alarmCount = 0;
bool stop = false;	


int main(void)
{
	DDRD = 0b10000000;
	PORTC |= (1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2) | (1<<PORTC3);
	ds1307::rtc_t rtc;

	//Setting time to the RTC
	rtc.seconds =  0x00; //
	rtc.minute =  0x00;
	rtc.hour = 0x10;	
	rtc.weekDay = 0x05;
	rtc.date = 0x06;
	rtc.month = 0x08;
	rtc.year = 0x21;	//27th May 2021
	
	DS1307.set_time(&rtc);
	lcd.LCD_Initializer();	//initialize the display (PORTB)

	while (1)
	{
		
		if (set==0){alarmclock.displayTime(); checkAlarm();}
		okbtn();
		upbtn();
		dwnbtn();
		backbtn();
	}
}

void display(){

	if (set == 1){
		lcd.LCD_Clear();
		lcd.LCD_String(Menu[currentscreenset1][0]);        //Write string on 1st line of LCD
		lcd.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd.LCD_String(Menu[currentscreenset1][1]);
		_delay_ms(500);
	}
	else if ((set == 2) & (currentscreenset1 == 0)){
		char* txtHr;
		char* txtMin;
		lcd.LCD_Clear();
		int* alarmTime = alarmclock.setNewAlarm();
		allAlarms[alarmCount][0] = alarmTime[0];
		allAlarms[alarmCount][1] = alarmTime[1];
		allAlarms[alarmCount][2] = 1;
		allAlarms[alarmCount][3] = 1;

		txtHr = alarmclock.int_to_char(alarmTime[0]);
		allAlarmsMenu[alarmCount][7] = 'O'; //optional
		allAlarmsMenu[alarmCount][8] = 'N'; //
		allAlarmsMenu[alarmCount][9] = ' ';

		alarmChangeList[alarmCount][0] = txtHr[0]; 
		alarmChangeList[alarmCount][1] = txtHr[1];

		txtMin = alarmclock.int_to_char(alarmTime[1]);

		alarmChangeList[alarmCount][3] = txtMin[0];
		alarmChangeList[alarmCount][4] = txtMin[1];

		alarmCount += 1;
	}
	
	else if ((set == 2) & (currentscreenset1 == 1)){
		//All alarms menu
		lcd.LCD_Clear();
		lcd.LCD_String(allAlarmsMenu[currentscreenset21]);  
		lcd.LCD_Commandgiver(0xC0);                        
		lcd.LCD_String("CHANGE     BACK");

		_delay_ms(500);
	}
	else if ((set==3) & (currentscreenset1==1) ){//& (currentscreenset21 == 0 or 1 or 2 or 3 or 4)){		lcd.LCD_Clear();		changeAlarm(currentscreenset21);		_delay_ms(500);
	}
	else if ((set == 2) & (currentscreenset1 == 2)){
		alarmclock.setTimetoRTC();
		_delay_ms(500);
	}
	else if ((set == 2) & (currentscreenset1 == 3)){
		lcd.LCD_Clear();
		lcd.LCD_String(alarmtone[currentscreenset23][0]);                //Write string on 1st line of LCD
		lcd.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd.LCD_String(alarmtone[currentscreenset23][1]);
		_delay_ms(1000);
		if (currentscreenset23==0){
			music.tone(0);
		}
		else if (currentscreenset23==1){
			music.tone(1);
		}
		else if (currentscreenset23==2){
			music.tone(2);
		}
		else if (currentscreenset23==3){
			music.tone(3);
		}
		else if (currentscreenset23==4){
			music.tone(4);
		}
	}
	else if ((set == 2) & (currentscreenset1 == 4)){
		lcd.LCD_Clear();
		lcd.LCD_String(reset[0]);                //Write string on 1st line of LCD
		lcd.LCD_Commandgiver(0xC0);              //Go to 2nd line
		lcd.LCD_String(reset[0]);
		_delay_ms(500);
	}
}

void upbtn(){
	if (!(PINC &(1<<Up))){
		_delay_ms(50);
		if ((set == 1) & (currentscreenset1==0)){
			currentscreenset1=numofscreens1-1;
			display();
		}
		else if ((set == 1) & (currentscreenset1 != 0)){
			currentscreenset1 -= 1;
			display();
		}
		else if ((set == 2) & (currentscreenset1==1) & (currentscreenset21 == 0)){
			currentscreenset21=numofscreens21-1;
			display();
		}
		else if ((set == 2) & (currentscreenset1==1) & (currentscreenset21 != 0)){
			currentscreenset21 -= 1;
			display();
		}
		else if ((set == 2) & (currentscreenset1==3) & (currentscreenset23 == 0)){
			currentscreenset23=numofscreens21-1;
			display();
		}
		else if ((set == 2) & (currentscreenset1==3) & (currentscreenset23 != 0)){
			currentscreenset23 -= 1;
			display();
		}
	}
}

void dwnbtn(){
	_delay_ms(50);
	if (!(PINC &(1<<Down))){
		if ((set == 1) & (currentscreenset1==4)){
			currentscreenset1=0;
			display();
		}
		else if ((set == 1) & (currentscreenset1 != 4)){
			_delay_ms(10);
			currentscreenset1 += 1;
			display();
		}
		else if ((set == 2) & (currentscreenset1==1) & (currentscreenset21 == 4)){
			currentscreenset21=0;
			display();
		}
		else if ((set == 2) & (currentscreenset1==1) & (currentscreenset23 != 4)){
			currentscreenset21 += 1;
			display();
		}
		else if ((set == 2) & (currentscreenset1==3) & (currentscreenset23 == 4)){
			currentscreenset23 = 0;
			display();
		}
		else if ((set == 2) & (currentscreenset1==3) & (currentscreenset23 != 4)){
			currentscreenset23 += 1;
			display();
		}
	}
}

void okbtn(){
	_delay_ms(50);
	if (!(PINC & (1<<Ok))){	
		if (set==3){
			set = 0;
		display();}
		else {
			set+= 1;
		display();}
	}
}

void backbtn(){
	_delay_ms(50);
	if (!(PINC &(1<<Back))){
		if (set == 0){
			set = 0;
			display();
		}
		else {
			set-= 1;
			display();
		}
	}
}

void checkAlarm(){
	int currentHr, currentMin, alarmHr, alarmMin, alarmCheck, alOnOff;
	bool alarm;
	//checking time and ringing an alarm
	for (int i=0; i<alarmCount;i++){
		alarmHr = allAlarms[i][0];
		alarmMin = allAlarms[i][1];
		alarmCheck = allAlarms[i][2]; //only used within this loop to check of the alarm was turned on
		alOnOff = allAlarms[i][3]; //this value will be 1 if alarm is ON and 0 if OFF

		currentHr = DS1307.read_time(02);
		currentMin = DS1307.read_time(01);

		if (((currentHr != alarmHr) || (currentMin != alarmMin))){
			allAlarms[i][2] = 1;
			stop = false;
		}
		
		while (1){
			currentHr = DS1307.read_time(02);
			currentMin = DS1307.read_time(01);
			if ((currentHr == alarmHr) & (currentMin == alarmMin)  & ~(stop) & (alarmCheck==1) & (alOnOff==1)){
				//lcd.LCD_Clear();
				lcd.LCD_String_xy(0, 0, "     Alarm      ");
				lcd.LCD_String_xy(1, 0, "STOP            ");
				//PORTD |= (1<<PORTD7);
				music.tone(0);
				allAlarms[i][2] = 0;
				alarm = true;
			}
			else{
				if(alarm){lcd.LCD_Clear();alarm=false;/*PORTD &= ~(1<<PORTD7)*/;set=0;}
				break;
			}
			
			if (!(PINC & (1<<Ok))){

				//PORTD &= ~(1<<PORTD7);
				lcd.LCD_Clear();
				stop = true;
				break;
			}
		}
	}
} 

void changeAlarm(int alPos){
	//alPos takes the position of the alarm that needs to be changed

	//--------------------Changing Alarms------------------------------
	bool delAlarm = false;
	uint8_t key;
	
	int min_al=0, hr_al=0;
	int n[6] = {6, 7, 9, 10};
	static int alarm[2];
	
	lcd.LCD_Clear();
	lcd.LCD_String_xy(0, 6, alarmChangeList[alPos]);
	lcd.LCD_String_xy(1, 0, "OK       DELETE");
	_delay_ms(200);
	for(uint8_t i=0;i<5;i++)
	{
		while(1)
		{
			key = keypad.GetKey();
			if (key == 1) {lcd.LCD_String_xy(0,n[i],"1");break;}
			if (key == 2) {lcd.LCD_String_xy(0,n[i],"2");break;}
			if (key == 3) {lcd.LCD_String_xy(0,n[i],"3");break;}
			if (key == 4) {lcd.LCD_String_xy(0,n[i],"4");break;}
			if (key == 5) {lcd.LCD_String_xy(0,n[i],"5");break;}
			if (key == 6) {lcd.LCD_String_xy(0,n[i],"6");break;}
			if (key == 7) {lcd.LCD_String_xy(0,n[i],"7");break;}
			if (key == 8) {lcd.LCD_String_xy(0,n[i],"8");break;}
			if (key == 9) {lcd.LCD_String_xy(0,n[i],"9");break;}
			if (key == 11) {lcd.LCD_String_xy(0,n[i],"0");key=0;break;}
			if (!(PINC & (1<<Ok))){i=8; break;}
			if (!(PINC & (1<<Back))){
				//deleting alarm
				allAlarms[alPos][0] = 0;
				allAlarms[alPos][1] = 0;
				allAlarms[alPos][2] = 0;
				allAlarms[alPos][3] = 0; //set alarm state as OFF

				allAlarmsMenu[alPos][7] = 'O'; //optional
				allAlarmsMenu[alPos][8] = 'F'; //
				allAlarmsMenu[alPos][9] = 'F';
 
				alarmChangeList[alPos][0] = '0'; 
				alarmChangeList[alPos][1] = '0'; 
				alarmChangeList[alPos][3] = '0'; 
				alarmChangeList[alPos][4] = '0'; 
				
				i = 8;
				delAlarm = true;
				//alarmCount -= 1;
				set=3;
				break;	
			}
			_delay_ms(200);
		}

		if (i == 0){hr_al+=key*10;}
		if (i == 1){hr_al+=key;}
		if (i == 2){min_al+=key*10;}
		if (i == 3){min_al+=key;}
	}
	//updating the lists with new alarm Hour and Min
	if (~(delAlarm)){
		char* txtHr;
		char* txtMin;
		allAlarms[alPos][0] = hr_al;
		allAlarms[alPos][1] = min_al;
		allAlarms[alPos][2] = 1;
		allAlarms[alPos][3] = 1;

		txtHr = alarmclock.int_to_char(hr_al);
		allAlarmsMenu[alPos][7] = 'O'; //optional
		allAlarmsMenu[alPos][8] = 'N'; 
		allAlarmsMenu[alPos][9] = ' ';

		alarmChangeList[alPos][0] = txtHr[0];
		alarmChangeList[alPos][1] = txtHr[1];

		txtMin = alarmclock.int_to_char(min_al);

		alarmChangeList[alPos][3] = txtMin[0];
		alarmChangeList[alPos][4] = txtMin[1];	
	} 
}
