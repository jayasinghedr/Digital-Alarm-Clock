#include <RTClib.h>

RTC_DS1307 rtc;

const int pinLED = 13;  // Alarm LED
const int pinLEDSnooze = 12; // Snooze LED
const int offButton = 2; 
const int snoozeButton = 3;
int snoozeTime = 1; //the alarm will be snoozed for 1 min
int alarmTime = 1920;
int currentTime, Hour, Min;
int off = 0; // indicates the state of the off button


void setup() {
  // put your setup code here, to run once: 

  rtc.begin();
  Serial.begin(9600);
  Serial.println("Alarm Timer");
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2021, 4, 3, 14, 35, 50));
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //set the current time to the RTC
    rtc.adjust(DateTime(__DATE__, __TIME__));
    //set a given time to the RTC
    //rtc.adjust(DateTime(2021, 4, 3, 14, 35, 50));
  }
  
  pinMode(pinLED, OUTPUT);
  pinMode(pinLEDSnooze, OUTPUT);
  pinMode(offButton, INPUT);
  pinMode(snoozeButton, INPUT_PULLUP);
  
}

void displayTime(){
  // displays the Real Time in the serial
  DateTime now = rtc.now();
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();
}



void loop() {
  // put your main code here, to run repeatedly:
 
  DateTime now = rtc.now();
  Hour = now.hour();
  Min = now.minute();
  
  currentTime = Hour*100+Min; // current time will be in the form hhmm
  displayTime();  
  delay(1000);

  if (digitalRead(offButton)){
    // changing the state of off button
    off = 1;
  }
      
  if ((alarmTime == currentTime) && (off == 0)){
    digitalWrite(pinLED, HIGH);   
  }
  
  if (off == 1){
    Serial.println("Alarm Off");
    digitalWrite(pinLED, LOW);
  }
  
  if (alarmTime != currentTime){
    digitalWrite(pinLED, LOW);
  }

  if (!digitalRead(snoozeButton) && (alarmTime == currentTime)) {
    // this will snooze the alarm for a given snoozetime
    digitalWrite(pinLED, LOW);
    alarmTime += snoozeTime;
    Serial.print("New Alarm : ");
    Serial.print(alarmTime);
    Serial.println();
    digitalWrite(pinLEDSnooze, HIGH);   // snooze LED (pinLEDSnooze) will light up for a second to
    delay(1000);                        // indicate that the alarm was snoozed
    digitalWrite(pinLEDSnooze, LOW);
  }

  if (!digitalRead(snoozeButton) && (alarmTime != currentTime)){
    // if the snooze button is pressed while the alarm is not activated
    // following message will print
    Serial.println("Cannot snooze now");
    digitalWrite(pinLEDSnooze, HIGH);
    delay(1000);
    digitalWrite(pinLEDSnooze, LOW);
  }   
}
