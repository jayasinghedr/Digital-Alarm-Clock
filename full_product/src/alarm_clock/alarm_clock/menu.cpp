/*
 * CPPFile1.cpp
 *
 * Created: 20-Jun-21 11:10:44 AM
 *  Author: Acer
 */ 
 #define F_CPU 8000000L
 #include <avr/io.h>
 #define __DELAY_BACKWARD_COMPATIBLE__	
 #include <util/delay.h>
 #include "ds1307.h"
 #include "LCD_Display.h"
 #include "AlarmClock.h"
 #include "Get_key.h"
 #include "music_notations.h"
 #include "menu.h"
 
 #define Up		PINC0
 #define Down	PINC1
 #define Ok		PINC2
 #define Back	PINC3
 #define SPEAKER_PORT PORTD
 #define SPEAKER_DDR DDRD
 #define SPEAKER_PIN 7

 
 LCD_Display lcd_2;
 music_notations music;
 AlarmClock alarmclock_1;
 
 
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
char Menu[5][2][16] = {{"New Alarm","ok  back"},{"All Alarms","ok  back"},{"Set Time","ok  back"},{"Alarm Tone","ok  back"},{"Reset","ok  back"}};
//char newalarm[][16]	= {"alarm","set  back"} ;
char allalarms[5][2][16] = {{"alarm 1","ok  back"},{"alarm 2","ok  back"},{"alarm 3","ok  back"},{"alarm 4","ok  back"},{"alarm 5","ok  back"}};
//char settime[][16] = {"time","ok  back"};
char alarmtone[5][2][16] = {{"got","ok  back"},{"pirates","ok  back"},{"starwars","ok  back"},{"coffin dance","ok  back"},{"take on me","ok  back"}};
char reset[][16] = {"reset all"};

int alarms[10][2]={};

void menu::display(){
	if (set == 0){
		/*lcd_2.LCD_Clear();
		lcd_2.LCD_String(initialdis[0]);                //Write string on 1st line of LCD
		lcd_2.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd_2.LCD_String(initialdis[1]);
		_delay_ms(1000);*/
		lcd_2.LCD_Clear();
		alarmclock_1.displayTime();
		//lcd_2.LCD_Clear();
	}
	else if (set == 1){
		lcd_2.LCD_Clear();
		lcd_2.LCD_String(Menu[currentscreenset1][0]);                //Write string on 1st line of LCD
		lcd_2.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd_2.LCD_String(Menu[currentscreenset1][1]);
		_delay_ms(1000);
	}
	else if ((set == 2) & (currentscreenset1 == 0)){
		lcd_2.LCD_Clear();
		/*lcd_2.LCD_String(newalarm[0]);                //Write string on 1st line of LCD
		lcd_2.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd_2.LCD_String(newalarm[1]);
		_delay_ms(1000);*/
		
		//int alarm=alarmclock_1.setNewAlarm();
		
	}
	else if ((set == 2) & (currentscreenset1 == 1)){
		lcd_2.LCD_Clear();
		lcd_2.LCD_String(allalarms[currentscreenset21][0]);                //Write string on 1st line of LCD
		lcd_2.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd_2.LCD_String(allalarms[currentscreenset21][1]);
		_delay_ms(1000);
	}
	else if ((set == 2) & (currentscreenset1 == 2)){
		//lcd_2.LCD_Clear();
		/*lcd_2.LCD_String(settime[0]);                //Write string on 1st line of LCD
		lcd_2.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd_2.LCD_String(settime[1]);
		_delay_ms(1000);*/
		alarmclock_1.setTimetoRTC();
	}
	else if ((set == 2) & (currentscreenset1 == 3)){
		lcd_2.LCD_Clear();
		lcd_2.LCD_String(alarmtone[currentscreenset23][0]);                //Write string on 1st line of LCD
		lcd_2.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd_2.LCD_String(alarmtone[currentscreenset23][1]);
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
		lcd_2.LCD_Clear();
		lcd_2.LCD_String(reset[0]);                //Write string on 1st line of LCD
		lcd_2.LCD_Commandgiver(0xC0);                        //Go to 2nd line
		lcd_2.LCD_String(reset[0]);
		_delay_ms(1000);
	}
}
void menu::upbtn(){
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
void menu::dwnbtn(){
	if (PINC &(1<<Down)){
		if ((set == 1) & (currentscreenset1==4)){
			currentscreenset1=0;
			display();
		}
		else if ((set == 1) & (currentscreenset1 != 4)){
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
void menu::okbtn(){
	if (PINC &(1<<Ok)){
		if (set==2){
			set = 0;
		display();}
		else {
			set+= 1;
		display();}
	}
}
void menu::backbtn(){
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

 