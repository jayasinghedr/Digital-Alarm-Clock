#include <LiquidCrystal.h> //starting up the lcd display
int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

int red_led =6;     //variables for the LED's
int green_led =5;
int blue_led =4;

int red_button=3;   //variables's for the button's
int green_button=2;
int blue_button=0;

int button_state_red=0; //initial button state
int button_state_green=0;
int button_state_blue=0;

int dt=200;         //delay variables

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);     //command to start the lcd
pinMode(red_led,OUTPUT);  //led as a output parameter
pinMode(red_button,INPUT);// button as a input parameter
 
pinMode(green_led,OUTPUT);
pinMode( green_button,INPUT);  

pinMode( blue_led,OUTPUT); 
pinMode(blue_button,INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:

button_state_red= digitalRead( red_button);  // reading the button state
button_state_green= digitalRead( green_button);
button_state_blue= digitalRead( blue_button);

if (button_state_red==1){      //checking whether button is on
  digitalWrite(red_led,HIGH);  //lighting on the led
  lcd.setCursor(0,0);
  lcd.print("YOU HAVE PRESSED"); // display the text in lcd
  lcd.setCursor(0,1);
  lcd.print("THE RED BUTTON");
  delay(dt);
  lcd.clear();
}

if (button_state_red==0){       // checking whether button is on
  digitalWrite(red_led,LOW);    //lighting off the led
}

if (button_state_green==1){
  digitalWrite(green_led,HIGH);
  lcd.setCursor(0,0);
  lcd.print("YOU HAVE PRESSED");
  lcd.setCursor(0,1);
  lcd.print("THE GREEN BUTTON");
  delay(dt);
  delay(dt);
  lcd.clear();
}

if (button_state_green==0){
  digitalWrite(green_led,LOW);
}

if (button_state_blue==1){
  digitalWrite(blue_led,HIGH);
  lcd.setCursor(0,0);
  lcd.print("YOU HAVE PRESSED");
  lcd.setCursor(0,1);
  lcd.print("THE BLUE BUTTON");
  delay(dt);
  delay(dt);
  lcd.clear();
}

if (button_state_blue==0){
  digitalWrite(blue_led,LOW);
}

}
