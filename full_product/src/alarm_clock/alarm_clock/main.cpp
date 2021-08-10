
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
#define Speaker PORTD7

void display();
void okbtn();
void upbtn();
void backbtn();
void dwnbtn();
void checkAlarm();
bool changeAlarm(int alPos);
void resetAll();

ds1307 DS1307;
LCD_Display lcd;
Get_key keypad;
AlarmClock alarmclock;
music_notations music;

int set = 0;                               // this variable indicates how many times has the ok button pressed
const int numofscreens_menu = 4;           // number of screens in main menu option(there are 4 screens-set alarm,set time,alarm tone,reset) 
int currentscreen_menu = 0;                // index of currently displaying screen of menu option
const int numofscreens_setalarm = 5;       // number of screens in set alarm option(there are 5 screens-alarm 1,alarm 2,alarm 3,alarm 4,alarm 5)
int currentscreen_setalarm = 0;            // index of currently displaying screen of set alarm option
const int numofscreens_settime = 1;        // number of screens in set time option
int currentscreen_settime = 0;             // index of currently displaying screen of set time option
const int numofscreens_alarmtone = 5;      // number of screens in alarm tone option(there are 5 screens-GOT,Pirates of the Caribbean,Star Wars, Astronomia, Take in me )
int currentscreen_alarmtone = 0;           // index of currently displaying screen of alarm tone option
const int numofscreens_reset = 1;          // number of screens in reset option
int currentscreen_reset = 0;               // index of currently displaying screen of reset option


char Menu[4][2][16] = {	//main menu with 4 options
	{"1.Set Alarms","OK         BACK"},
	{"2.Set Time","OK         BACK"},
	{"3.Alarm Tone","OK         BACK"},
	{"4.Reset","OK         BACK"}
};


char allAlarmsMenu[5][16] = {"Alarm1 __:__", "Alarm2 __:__", "Alarm3 __:__", "Alarm4 __:__","Alarm5 __:__"};	//this list displays the alarms we have already set  

char alarmChangeList[5][16] = {"00:00", "00:00", "00:00", "00:00", "00:00"};	//these values are changed when we change the alarms (as char arrays)


char alarmtone[5][2][16] = {	//5 alarm tones
	{"1.GOT","OK             "},
	{"2.PIRATES","OK             "},
	{"3.STARWARS","OK             "},
	{"4.ASTRONOMIA","OK             "},
	{"5.TAKE IN ME","OK             "}
};


int allAlarms[5][4];	//saves all the alarms in integer values [Alarm Hr, AlarmMin, 1/0, ON/OFF]

bool stop = false;	//this variable checks if the alarm if stopped


int main(void)
{
	DDRD = (1<<Speaker);	//setting the PORTD7 as output for speaker
	PORTC |= (1<<PORTC0) | (1<<PORTC1) | (1<<PORTC2) | (1<<PORTC3); //enabling the internal pull ups for the 4 buttons

	//Setting time to the RTC
	ds1307::rtc_t rtc;
	rtc.seconds =  0x00; 
	rtc.minute =  0x00;
	rtc.hour = 0x10;	//Initial Time set to 10:00:00 
	rtc.weekDay = 0x02;
	rtc.date = 0x10;
	rtc.month = 0x08;
	rtc.year = 0x21; //10th Aug 2021 Tue
	DS1307.set_time(&rtc);

	lcd.LCD_Initializer();	//initializes the display to PORTB

	while (1)
	{
		
		if (set==0){alarmclock.displayTime(); checkAlarm();}	// alarm checking & displaying time are done on the main screen (set = 0) 
		okbtn();
		upbtn();
		dwnbtn();
		backbtn();
	}
}
// function for displaying screens on lcd display
void display(){
    //menu option
	if (set == 1){
		lcd.LCD_Clear();
		lcd.LCD_String(Menu[currentscreen_menu][0]);        
		lcd.LCD_Commandgiver(0xC0);                        
		lcd.LCD_String(Menu[currentscreen_menu][1]);
		_delay_ms(500);
	}
	//set alarms option
	else if ((set == 2) & (currentscreen_menu == 0)){
		lcd.LCD_Clear();
		lcd.LCD_String(allAlarmsMenu[currentscreen_setalarm]);  
		lcd.LCD_Commandgiver(0xC0);                        
		lcd.LCD_String("CHANGE     BACK");

		_delay_ms(500);
	}
	//change alarm option
	else if ((set==3) & (currentscreen_menu==0) ){		bool g = false;		lcd.LCD_Clear();		g = changeAlarm(currentscreen_setalarm); 		if (g) {set=1;}		_delay_ms(500);
	}
	//set time option
	else if ((set == 2) & (currentscreen_menu == 1)){
		bool go;
		go = alarmclock.setTimetoRTC();
		if (go) {set=2;}
		_delay_ms(500);
	}
	//alarm tone option
	else if ((set == 2) & (currentscreen_menu == 2)){
		lcd.LCD_Clear();
		lcd.LCD_String(alarmtone[currentscreen_alarmtone][0]);                
		lcd.LCD_Commandgiver(0xC0);                        
		lcd.LCD_String(alarmtone[currentscreen_alarmtone][1]);
		_delay_ms(1000);
		if (currentscreen_alarmtone==0){
			music.tone(0);
		}
		else if (currentscreen_alarmtone==1){
			music.tone(1);
		}
		else if (currentscreen_alarmtone==2){
			music.tone(2);
		}
		else if (currentscreen_alarmtone==3){
			music.tone(3);
		}
		else if (currentscreen_alarmtone==4){
			music.tone(4);
		}
	}
	//reset option
	else if ((set == 2) & (currentscreen_menu == 3)){
		lcd.LCD_Clear();
		resetAll();
		_delay_ms(500);
		set = 0;
	}
}
// function for up button 
void upbtn(){
	if (!(PINC &(1<<Up))){
		_delay_ms(50);
		// go upwards in main menu 
		if ((set == 1) & (currentscreen_menu==0)){
			currentscreen_menu=numofscreens_menu-1;
			display();
		}
		else if ((set == 1) & (currentscreen_menu != 0)){
			currentscreen_menu -= 1;
			display();
		}
		// go upwards in set alarm menu
		else if ((set == 2) & (currentscreen_menu==0) & (currentscreen_setalarm == 0)){
			currentscreen_setalarm=numofscreens_setalarm-1;
			display();
		}
		else if ((set == 2) & (currentscreen_menu==0) & (currentscreen_setalarm != 0)){
			currentscreen_setalarm -= 1;
			display();
		}
		// go upwards in alarm tone menu
		else if ((set == 2) & (currentscreen_menu==2) & (currentscreen_alarmtone == 0)){
			currentscreen_alarmtone=numofscreens_alarmtone-1;
			display();
		}
		else if ((set == 2) & (currentscreen_menu==2) & (currentscreen_alarmtone != 0)){
			currentscreen_alarmtone -= 1;
			display();
		}
	}
}
// function for down button 
void dwnbtn(){
	if (!(PINC &(1<<Down))){
		_delay_ms(50);
		// go downwards in main menu
		if ((set == 1) & (currentscreen_menu==3)){
			currentscreen_menu=0;
			display();
		}
		else if ((set == 1) & (currentscreen_menu != 3)){
			_delay_ms(10);
			currentscreen_menu += 1;
			display();
		}
		// go downwards in set alarm menu
		else if ((set == 2) & (currentscreen_menu==0) & (currentscreen_setalarm == 4)){
			currentscreen_setalarm=0;
			display();
		}
		else if ((set == 2) & (currentscreen_menu==0) & (currentscreen_setalarm != 4)){
			currentscreen_setalarm += 1;
			display();
		}
		// go downwards in alarm tone menu
		else if ((set == 2) & (currentscreen_menu==2) & (currentscreen_alarmtone == 4)){
			currentscreen_alarmtone = 0;
			display();
		}
		else if ((set == 2) & (currentscreen_menu==2) & (currentscreen_alarmtone != 4)){
			currentscreen_alarmtone += 1;
			display();
		}
	}
}
// function for ok button
// go to the selected option
void okbtn(){
	
	if (!(PINC & (1<<Ok))){	
		_delay_ms(200);
		if (set==3){
			set = 0;
		display();}
		else {
			set+= 1;
		display();}
	}
}
// function for back button
// go back to the previously selected option
void backbtn(){
	
	if (!(PINC &(1<<Back))){
		_delay_ms(50);
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
	//This function goes through all the alarms in allAlarms list
	//and if any alarm time is equal to the current time it turns on the speaker
	int currentHr, currentMin, alarmHr, alarmMin, alarmCheck, alOnOff;
	bool alarm; 
	for (int i=0; i<5;i++){ // checks through each alarm separately 
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
			currentHr = DS1307.read_time(02);	//gets the time from the RTC
			currentMin = DS1307.read_time(01);
			if ((currentHr == alarmHr) & (currentMin == alarmMin)  & ~(stop) & (alarmCheck==1) & (alOnOff==1)){
				//if all the above conditions are met the speaker will start playing the tone
				lcd.LCD_String_xy(0, 0, "     Alarm      ");	//LCD will display the following message
				lcd.LCD_String_xy(1, 0, "STOP            ");	// |     Alarm      |
																// |Stop            |
				music.tone(currentscreen_alarmtone);			// the tone selected from the menu will be played
				allAlarms[i][2] = 0;
				alarm = true;
			}
			else{
				if(alarm){lcd.LCD_Clear();alarm=false;set=0;}	//after 1 minute the alarm will stop ringing
				break;
			}
			
			if (!(PINC & (1<<Ok))){	//if we press the Ok button while the alarm is playing
				lcd.LCD_Clear();	//it will stop the alarm
				set=0;				//and return back to displaying current time
				display();
				stop = true;
				break;
			}
		}
	}
} 

bool changeAlarm(int alPos){
	//this function is used to Set, Change & Delete alarms
	//alPos takes the position of the alarm that needs to be changed
	bool delAlarm = false;	
	bool noChange = false;
	bool backToMenu = false;
	uint8_t key;
	
	int min_al=0, hr_al=0;
	int n[6] = {6, 7, 9, 10};
	
	lcd.LCD_Clear();
	lcd.LCD_String_xy(0, 6, alarmChangeList[alPos]); //display the current alarm time or 00:00 is alarm is not set 
	lcd.LCD_String_xy(1, 0, "OK       DELETE");	
	_delay_ms(200);
	for(uint8_t i=0;i<5;i++)
	{
		//we can change the alarm values through keypad input
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
			if (!(PINC & (1<<Ok))){	
				//when okay button is pressed the alarm will be saved and the used will 
				//exit the current screen
				if (i==0){noChange=true;}
				i=8; 
				break;
			}
			if (!(PINC & (1<<Back))){
				//when we press the back button the saved alarms will be deleted
				//the user will exit the screen
				allAlarms[alPos][0] = 0;
				allAlarms[alPos][1] = 0;
				allAlarms[alPos][2] = 0;
				allAlarms[alPos][3] = 0; //set alarm state as OFF

				allAlarmsMenu[alPos][7] = '_'; //all alarms menu will change back tp -> Alarm# __:__ 
				allAlarmsMenu[alPos][8] = '_'; 
				allAlarmsMenu[alPos][10] = '_';
				allAlarmsMenu[alPos][11] = '_';
 
				alarmChangeList[alPos][0] = '0'; //alarm screen will change back to -> 00:00
				alarmChangeList[alPos][1] = '0'; 
				alarmChangeList[alPos][3] = '0'; 
				alarmChangeList[alPos][4] = '0'; 
				
				i = 8;
				delAlarm = true;
				set=3;
				break;	
			}
			_delay_ms(200);
		}

		if (i == 0){hr_al+=key*10;}	// new alarm hour 
		if (i == 1){hr_al+=key;}
		if (i == 2){min_al+=key*10;} //new alarm min
		if (i == 3){min_al+=key;}
	}
	//updating the lists with new alarm Hour and Min
	if (!(delAlarm || noChange)){ 
		//if the Delete (Back button was not pressed)
		//the alarm saving in done by this code
		char* txtHr;
		char* txtMin;
		if (hr_al >= 24 ){hr_al = 0;}
		if (min_al >= 60){min_al = 0;}
		allAlarms[alPos][0] = hr_al;
		allAlarms[alPos][1] = min_al;
		allAlarms[alPos][2] = 1;
		allAlarms[alPos][3] = 1;

		txtHr = alarmclock.int_to_char(hr_al);
		allAlarmsMenu[alPos][7] = txtHr[0];
		allAlarmsMenu[alPos][8] = txtHr[1]; 

		alarmChangeList[alPos][0] = txtHr[0];
		alarmChangeList[alPos][1] = txtHr[1];

		txtMin = alarmclock.int_to_char(min_al);

		alarmChangeList[alPos][3] = txtMin[0];
		alarmChangeList[alPos][4] = txtMin[1];	

		allAlarmsMenu[alPos][10] = txtMin[0];
		allAlarmsMenu[alPos][11] = txtMin[1];

		backToMenu = true;
	} 
	return backToMenu;	//after saving the alarm user can go back to the Set Alarms menu
}

void resetAll(){
	//this function resets all the values already stored in the alarm clock
	lcd.LCD_String_xy(0, 0, "Resetting All");
	for (int i=0; i<5; i++){
		//values in all the alarm related lists will be set to default
		allAlarms[i][0] = 0;
		allAlarms[i][1] = 0;
		allAlarms[i][2] = 0;
		allAlarms[i][3] = 0; //set alarm state as OFF

		allAlarmsMenu[i][7] = '_'; 
		allAlarmsMenu[i][8] = '_';
		allAlarmsMenu[i][10] = '_';
		allAlarmsMenu[i][11] = '_';
	
		alarmChangeList[i][0] = '0';
		alarmChangeList[i][1] = '0';
		alarmChangeList[i][3] = '0';
		alarmChangeList[i][4] = '0';
	}

	ds1307::rtc_t rtc;

	//Setting time to the RTC
	rtc.seconds =  0x00;
	rtc.minute =  0x00;
	rtc.hour = 0x00;	//Initial Time set to 10:00:00
	rtc.weekDay = 0x01;
	rtc.date = 0x06;
	rtc.month = 0x08;
	rtc.year = 0x21; //10th Aug 2021 Tue
	DS1307.set_time(&rtc);
	_delay_ms(500);
	
	set = 0;	//goes back to the main display
	currentscreen_menu=0; 
	currentscreen_setalarm=0;
	currentscreen_alarmtone=0;
}

