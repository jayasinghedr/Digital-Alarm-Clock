/*
 * buzzer.c
 *
 * Created: 11-May-21 12:19:54 PM
 * Author : Tilan
 */ 

# define F_CPU 8000000UL
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include "music_notations.h"

// speaker is connected to the port c pin 0
#define SPEAKER_PORT PORTC    
#define SPEAKER_DDR DDRC     
#define SPEAKER_PIN 0

// two buttons are connected to the portB pin 6 & 7. one button is for play/pause a melody. other one for select a melody
#define BUTTON_PIN PINB
#define PLAYBUTTON_PIN 0
#define PAUSEBUTTON_PIN 0
#define NEXTBUTTON_PIN 1


// function to create a sound of frequency of "frequency" for time duration of "duration"
void playthenote(float frequency, float duration);

// function to select the next melody                  
void NextMelody();

// function to play the melody
void playthemelody(int Melody[], int MelodyDuration[], int size);


// this variable helps to find the index of a melody 
int playing=0;

// index of the currently selected melody
int selectedmelody=0;

// time delay for get rid of bouncing effect
int debouncing_delay = 700;

// number of notes of each melody notations
int sizeofgot = sizeof(GOT)/sizeof(GOT[0]);
int sizeofpirates = sizeof(Pirates)/sizeof(Pirates[0]);
int sizeofstarwars = sizeof(StarWars)/sizeof(StarWars[0]);
int sizeofcoffindance = sizeof(CoffinDance)/sizeof(CoffinDance[0]);
int sizeoftakeonme = sizeof(TakeOnMe)/sizeof(TakeOnMe[0]);

int main(void)
{
	// declaring portB pin 6 & 7 as inputs
	DDRB= 0b11111100;
	
	
	while (1)
	 {
		 // selecting the melody that want to play
		 NextMelody();
		 // check whether the play button is pressed. if so, playing the selected melody
		 if ( BUTTON_PIN & (1<<PLAYBUTTON_PIN)){
			_delay_ms(debouncing_delay);
			if (selectedmelody == 0){
				 playthemelody(GOT, GOTDurations, sizeofgot);
		    }
			else if (selectedmelody == 1){
				 playthemelody(Pirates, PiratesDurations, sizeofpirates);
			}
			else if (selectedmelody == 2){
				 playthemelody(StarWars, StarWarsDurations, sizeofstarwars);
			}
			else if (selectedmelody == 3){
				 playthemelody(CoffinDance, CoffinDanceDurations, sizeofcoffindance);
		    }
			else if (selectedmelody == 4){
				 playthemelody(TakeOnMe, TakeOnMeDurations, sizeoftakeonme);
			}
		}
	}
}


// function to select a melody
void NextMelody()
{
	// check whether the next button is pressed. if so, finding the index of the melody
	if ( BUTTON_PIN & (1<<NEXTBUTTON_PIN)){
		_delay_ms(debouncing_delay);
		playing += 1;
		selectedmelody = playing % 5;
	}
}

// function to generate sound using square waves 
void playthenote(float frequency, float duration)
{
	long int i,cycles;
	float half_period;
	float period;
	
	// "period" is the wavelength calculated from frequency using the formula "period" = 1 / f.
	// We output 5 V for a length of time determined by half period (period/2), and then output 0 V, for the same length of time.
	
	if (frequency != 0){
		period=(1/frequency)*1000;  // period in mile seconds
	    cycles=duration/period;
	    half_period = period/2;
		
		SPEAKER_DDR |= (1 << SPEAKER_PIN);

	    for (i=0;i<cycles;i++)
	    {
		    _delay_ms(half_period);
		    SPEAKER_PORT |= (1 << SPEAKER_PIN);
		    _delay_ms(half_period);
		    SPEAKER_PORT &= ~(1 << SPEAKER_PIN);
	    }
	}
	else {
		_delay_ms(duration);   // rest 
	}

	return;
}

// function to play the selected melody
void playthemelody(int Melody[], int MelodyDuration[], int size)
{ 
	// melody will play until the pause button is pressed. 
	int still_playing = 1;
	while(still_playing){
	for (int x=0; x<size; x++){
		playthenote(Melody[x],MelodyDuration[x]);
		_delay_us(MelodyDuration[x]);
		// check whether the pause button is pressed. if so, stopping the melody
		if ( BUTTON_PIN & (1<<PAUSEBUTTON_PIN)){
			 _delay_ms(debouncing_delay);
			 still_playing = 0;
			 break;
		 }
	 }
   }
}
