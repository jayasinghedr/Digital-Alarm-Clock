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
#include "Functions.h"


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
		 // check whether the play button is pressed. if so, play the selected melody
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

