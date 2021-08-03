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
void changeAlarm();

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


//char initialdis[][16]={"Welcome !","menu"};
char Menu[5][2][16] = {
	{"New Alarm","OK         BACK"},
	{"All Alarms","OK         BACK"},
	{"Set Time","OK         BACK"},
	{"Alarm Tone","OK         BACK"},
	{"Reset","OK         BACK"}
};

char allAlarmsMenu[5][2][16] = {
	{"Alarm1 __:__","CHANGE     BACK"},
	{"Alarm2 __:__","CHANGE     BACK"},
	{"Alarm3 __:__","CHANGE     BACK"},
	{"Alarm4 __:__","CHANGE     BACK"},
	{"Alarm5 __:__","CHANGE     BACK"}
};

char alarmChangeList[5][2][16] = {
	{"__:__","OK       DELETE"},
	{"__:__","OK       DELETE"},
	{"__:__","OK       DELETE"},
	{"__:__","OK       DELETE"},
	{"__:__","OK       DELETE"}
};

char alarmtone[5][2][16] = {
	{"GOT","OK         BACK"},
	{"PIRATES","OK         BACK"},
	{"STARWARS","OK         BACK"},
	{"ASTRONOMIA","OK         BACK"},
	{"TAKE IN ME","OK         BACK"}
};
char reset[][16] = {"reset all"};

int allAlarms[10][3];	//saves all the alarms in int values

int alarmCount = 0;
bool stop=false;	


int main(void)
{
	DDRD = 0b10000000;
	ds1307::rtc_t rtc;

	// Setting time to the RTC
	rtc.seconds =  0x00; //
	rtc.minute =  0x00;
	rtc.hour = 0x12;	//  20:17:00
	rtc.weekDay = 0x05;
	rtc.date = 0x31;
	rtc.month = 0x05;
	rtc.year = 0x21;	//27th May 2021
	
	DS1307.set_time(&rtc);

	lcd.LCD_Initializer();	//initialize the display (PORTB)

	while (1)
	{
		
		checkAlarm();
		if (set==0){alarmclock.displayTime();}
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
		_delay_ms(1000);
	}
	else if ((set == 2) & (currentscreenset1 == 0)){
		char* txtHr;
		char* txtMin;
		lcd.LCD_Clear();
		int* alarmTime = alarmclock.setNewAlarm();
		allAlarms[alarmCount][0] = alarmTime[0];
		allAlarms[alarmCount][1] = alarmTime[1];
		allAlarms[alarmCount][2] = 1;

		txtHr = alarmclock.int_to_char(alarmTime[0]);
		allAlarmsMenu[alarmCount][0][7] = txtHr[0]; //optional
		allAlarmsMenu[alarmCount][0][8] = txtHr[1]; //

		//alarmChangeList[alarmCount][0][0] = txtHr[0]; 
		//alarmChangeList[alarmCount][0][1] = txtHr[1];

		txtMin = alarmclock.int_to_char(alarmTime[1]);
		allAlarmsMenu[alarmCount][0][10] = txtMin[0]; // optional
		allAlarmsMenu[alarmCount][0][11] = txtMin[1]; //

		//alarmChangeList[alarmCount][0][3] = txtMin[0];
		//alarmChangeList[alarmCount][0][4] = txtMin[1];

		alarmCount += 1;
	}
	else if ((set == 2) & (currentscreenset1 == 1)){
		//All alarms menu
		lcd.LCD_Clear();
		lcd.LCD_String(allAlarmsMenu[currentscreenset21][0]);  
		lcd.LCD_Commandgiver(0xC0);                        
		lcd.LCD_String(allAlarmsMenu[currentscreenset21][1]);

		//when OK button (CHANGE in this screen) is pressed 
		//next Screen will appear as follows
		//   |     16:30       |
		//   | OK        DELETE|
		
		_delay_ms(1000);
	}
	else if ((set==3) & (currentscreenset1==1) ){//& (currentscreenset21 == 0 or 1 or 2 or 3 or 4)){
		lcd.LCD_Clear();
		lcd.LCD_String("     16:30       ");                //Write string on 1st line of LCD
		lcd.LCD_Commandgiver(0xC0);              //Go to 2nd line
		lcd.LCD_String("OK        DELETE");
		_delay_ms(1000);
		
	}
	else if ((set == 2) & (currentscreenset1 == 2)){
		alarmclock.setTimetoRTC();
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
		_delay_ms(1000);
	}
	
}

void upbtn(){
	if (PINC &(1<<Up)){
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
	if (PINC &(1<<Down)){
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
	if (PINC & (1<<Ok)){
		if (set==3){
			set = 0;
		display();}
		else {
			set+= 1;
		display();}
	}
}

void backbtn(){
	if (PINC &(1<<Back)){
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
	int currentHr, currentMin, alarmHr, alarmMin, currentAlarm, alarmCheck;
	bool alarm;
	//checking time and ringing an alarm
	for (int i=0; i<alarmCount;i++){
		alarmHr = allAlarms[i][0];
		alarmMin = allAlarms[i][1];
		alarmCheck = allAlarms[i][2]; //if the alarm is already played this value will be 0 otherwise 1

		currentHr = DS1307.read_time(02);
		currentMin = DS1307.read_time(01);

		if (((currentHr != alarmHr) || (currentMin != alarmMin)) /*& (currentAlarm==i)*/){
			allAlarms[i][2] = 1;
			stop = false;
		}
		
		while (1){
			currentHr = DS1307.read_time(02);
			currentMin = DS1307.read_time(01);
<<<<<<< HEAD
			if ((currentHr == alarmHr) & (currentMin == alarmMin)  /*& ~(stop)*/){
				lcd.LCD_Clear();
				lcd.LCD_String_xy(0, 0, "     Alarm      ");
				lcd.LCD_String_xy(1, 0, "STOP            ");
				//PORTD |= (1<<PORTD7);
				music.tone(currentscreenset23);
=======
			if ((currentHr == alarmHr) & (currentMin == alarmMin)  & ~(stop) & (alarmCheck==1)){
				//lcd.LCD_Clear();
				lcd.LCD_String_xy(0, 0, "     Alarm      ");
				lcd.LCD_String_xy(1, 0, "STOP            ");
				PORTD |= (1<<PORTD7);
				allAlarms[i][2] = 0;
>>>>>>> master
				currentAlarm = i;
				alarm = true;
			}
			else{
				if(alarm){lcd.LCD_Clear();alarm=false;PORTD &= ~(1<<PORTD7);set=0;}
				break;
			}
			
			if (PINC & (1<<Ok)){
				PORTD &= ~(1<<PORTD7);
				lcd.LCD_Clear();
				stop = true;
				break;
			}
		}
	}
} 
