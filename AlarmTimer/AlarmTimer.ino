#include <RTClib.h>

RTC_DS1307 rtc;

int pinLED = 13;  // Alarm LED
int pinLEDSnooze = 12; // Snooze LED
int offButton = 2; 
int snoozeButton = 3;
int snoozeTime = 1;
int alarmTime = 1436;
int currentTime, Hour, Min;
int off;


void setup() {
  // put your setup code here, to run once: 

  rtc.begin();
  Serial.begin(9600);
  Serial.println("Alarm Timer");

  //set the current time to the RTC
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //set a given time to the RTC
  rtc.adjust(DateTime(2021, 4, 3, 14, 35, 50));
  
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

  off = digitalRead(offButton);
      
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
    digitalWrite(pinLED, LOW);
    alarmTime += snoozeTime;
    Serial.print("New Alarm : ");
    Serial.print(alarmTime);
    Serial.println();
    digitalWrite(pinLEDSnooze, HIGH);
    delay(1000);
    digitalWrite(pinLEDSnooze, LOW);
  }

  if (!digitalRead(snoozeButton) && (alarmTime != currentTime)){
    Serial.println("Cannot snooze now");
    digitalWrite(pinLEDSnooze, HIGH);
    delay(1000);
    digitalWrite(pinLEDSnooze, LOW);
  }   
}
