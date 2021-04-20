#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//notes of "Take on me" song.
int TakeOnMe[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};
// 123
//Note durations of "Take on me" song.
int TakeOnMeDurations[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};

//Notes of the "Pirates of The Carribean" theme song.
int Pirates[] = {
    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
    NOTE_A4, NOTE_G4, NOTE_A4, 0,

    NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
    NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
    NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

    NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
    NOTE_D5, NOTE_E5, NOTE_A4, 0,
    NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
    NOTE_C5, NOTE_A4, NOTE_B4, 0 };

//Note durations of the "Pirates of The Carribean" theme song.
int PiratesDurations[] = {
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125,

    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125,
    250, 125, 250, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 375 };

//Notes of the "Game of Thrones" theme song.
int GOT[] ={
  392, 262, 311, 349, 392,262, 311, 349, 294, 349, 233, 294, 311, 349, 233, 311, 294, 262
};

//note durations of the "Game of Thrones" theme song.
int GOTDurations[] = {
  800, 800, 250, 250, 800, 800, 250, 250, 1250, 800, 800, 250, 250, 800, 800, 250, 250, 1250
};
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

//Notes of the "Star Wars" theme song.
int StarWars[]={
  a,a,a,f,cH,a,f,cH,a,0,eH,eH,eH,fH,cH,gS,f,cH,a,0,aH,a,a,aH,gSH,gH,fSH,fH,fSH,0,aS,dSH,dH,cSH,cH,b,cH,0
};

//Note durations of the "Star Wars" theme song.
int StarWarsDurations[]={
  500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 500,
  350, 150, 500, 350, 150, 650, 500, 500, 300, 150, 500, 325, 175,
  125, 125, 250, 375, 250, 500, 325, 175, 125, 125, 250, 500
};

//Note of the "Coffin Dance" melody.
int CoffinDance[] = {
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, 
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, 
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
  NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
  NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
  NOTE_G4, 0, NOTE_G4, NOTE_D5,
  NOTE_C5, 0, NOTE_AS4, 0,
  NOTE_A4, 0, NOTE_A4, NOTE_A4,
  NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4, 0, NOTE_G4, NOTE_D5,
  NOTE_C5, 0, NOTE_AS4, 0,
  NOTE_A4, 0, NOTE_A4, NOTE_A4,
  NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
  NOTE_G4,0, NOTE_G4, NOTE_AS5,
  NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
 };

//Note durations of the "Coffin Dance" melody.
int CoffinDanceDurations[] = {
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  };
  
int PlayButton=2;
int NextButton=3;


int PlayButtonState=0;
int NextButtonState=0;

int playing=0;
int currentplaying=0;


void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
  Serial.println("GOT");
}

//Function to display the next song in the serial monitor.
void nexttrack(){
  if (digitalRead(NextButton)== HIGH){
    if (NextButtonState==0){
      playing+=1;
      NextButtonState=1;
      currentplaying=playing%5;
      if (currentplaying==0){
        Serial.println("GOT");
        delay(1000);
        NextButtonState=0;}
      else if(currentplaying==1){
        Serial.println("Pirates of The Carribean");
        delay(1000);
        NextButtonState=0;}
      else if(currentplaying==2){
        Serial.println("Star Wars");
        delay(1000);
        NextButtonState=0;}
      else if(currentplaying==3){
        Serial.println("Coffin Dance");
        delay(1000);
        NextButtonState=0;}
      else if(currentplaying==4){
        Serial.println("Take On Me");
        delay(1000);
        NextButtonState=0;}
      
    }
  }
}
void loop()
{
  nexttrack();
  if (digitalRead(PlayButton)== HIGH){
    if(PlayButtonState==0){
      PlayButtonState=1;
      if (currentplaying==0){
        int n=0;
        while (n==0){
          for (int i=0; i<sizeof(GOT)/sizeof(GOT[0]); i++){
          tone(A0, GOT[i], GOTDurations[i]);
          delay(GOTDurations[i]);
          if (digitalRead(PlayButton)== HIGH){
              if (PlayButtonState==1){
                 PlayButtonState=0;
                 n=1;
                 break; }
            }
          nexttrack();
          }
        }
         }
      else if (currentplaying==1){
        int n=0;
        while (n==0){
           for (int i=0; i<sizeof(Pirates)/sizeof(Pirates[0]); i++){
           tone(A0, Pirates[i], PiratesDurations[i]);
           delay(PiratesDurations[i]);
           if (digitalRead(PlayButton)== HIGH){
              if (PlayButtonState==1){
                 PlayButtonState=0;
                 n=1;
                 break; }
            }
        nexttrack();
          }
        }
         }
      else if (currentplaying==2){
          int n=0;
          while (n==0){
          for (int i=0; i<sizeof(StarWars)/sizeof(StarWars[0]); i++){
          tone(A0, StarWars[i], StarWarsDurations[i]);
          delay(StarWarsDurations[i]);
          if (digitalRead(PlayButton)== HIGH){
              if (PlayButtonState==1){
                 PlayButtonState=0;
                 n=1;
                 break; }
            }
          nexttrack();
          }
          }
         }
      else if (currentplaying==3){
          int n=0;
          while (n==0){
          for (int i=0; i<sizeof(CoffinDance)/sizeof(CoffinDance[0]); i++){
          tone(A0, CoffinDance[i], 750 / CoffinDanceDurations[i]);
          int pauseBetweenNotes = 750 *1.3 / CoffinDanceDurations[i];
          delay(pauseBetweenNotes);
          if (digitalRead(PlayButton)== HIGH){
              if (PlayButtonState==1){
                 PlayButtonState=0;
                 n=1;
                 break; }
            }
          nexttrack();
            
          
          }
          }
         }
      else if (currentplaying==4){
          int n=0;
          while (n==0){
          for (int i=0; i<sizeof(TakeOnMe)/sizeof(TakeOnMe[0]); i++){
          tone(A0, TakeOnMe[i], 1000/ TakeOnMeDurations[i]);
          delay(1000 *1.3/ TakeOnMeDurations[i]);
          if (digitalRead(PlayButton)== HIGH){
              if (PlayButtonState==1){
                 PlayButtonState=0;
                 n=1;
                 break; }
            }
          nexttrack();
            }
          }
         }
      
    delay(1000);
    PlayButtonState=0;
    }
    
  }
}  
  
  
  
  
  
  
  
  
      
      
      
      
      
      
      

  
