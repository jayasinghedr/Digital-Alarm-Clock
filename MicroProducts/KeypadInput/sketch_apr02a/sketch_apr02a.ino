#include <Keypad.h>
const byte Rows = 4; //four rows
const byte Cols = 3; //three columns
char Keys[Rows][Cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[Rows] = {5,4,3,2};//pins relevant to the rows
byte colPins[Cols] = {6,7,8};//pins relevant to the columns
Keypad keypad = Keypad(makeKeymap(Keys),rowPins,colPins,Rows,Cols);
void setup() {
  Serial.begin(9600);
  // output pins
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}

void loop() {
  char key ;
  key = keypad.getKey();
  if(key)
  {
    switch(key)
    {case '1':{digitalWrite(A0, !digitalRead(A0));
             break;}
    case '2':{digitalWrite(A1, !digitalRead(A1));
             break;}
    case '3':{digitalWrite(A2, !digitalRead(A2));
             break;}
    case '4':{digitalWrite(A3, !digitalRead(A3));
             break;}
    case '5':{digitalWrite(A4, !digitalRead(A4));
             break;}
    case '6':{digitalWrite(A5, !digitalRead(A5));
             break;}

             
    case '7':{digitalWrite(9, !digitalRead(9));
             break;}
    case '8':{digitalWrite(10, !digitalRead(10));
             break;}
    case '9':{digitalWrite(11, !digitalRead(11));
             break;}
    case '*':{digitalWrite(10, !digitalRead(10));digitalWrite(9, !digitalRead(9));digitalWrite(11, !digitalRead(11));digitalWrite(A0, !digitalRead(A0));
             digitalWrite(A1, !digitalRead(A1));digitalWrite(A2, !digitalRead(A2));digitalWrite(A3, !digitalRead(A3));digitalWrite(A4, !digitalRead(A4));digitalWrite(A5, !digitalRead(A5));break;}
    case '#':{digitalWrite(A0,LOW);digitalWrite(A1,LOW);digitalWrite(A2,LOW);digitalWrite(A3,LOW);digitalWrite(A4,LOW);digitalWrite(A5,LOW);digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);break;}
    case '0':{digitalWrite(A0,HIGH);digitalWrite(A1,HIGH);digitalWrite(A2,HIGH);digitalWrite(A3,HIGH);digitalWrite(A4,HIGH);digitalWrite(A5,HIGH);digitalWrite(9,HIGH);digitalWrite(10,HIGH);digitalWrite(11,HIGH);break;}
           
   
    }
 }
}
