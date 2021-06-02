/*
 * IncFile1.h
 *
 * Created: 23-May-21 11:55:14 AM
 *  Author: Acer
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

// time delay for get rid of bouncing effect
int debouncing_delay = 700;

// this variable helps to find the index of a melody
int playing=0;

// index of the currently selected melody
int selectedmelody=0;

// speaker is connected to the port c pin 0
#define SPEAKER_PORT PORTC
#define SPEAKER_DDR DDRC
#define SPEAKER_PIN 0

// two buttons are connected to the portB pin 0 & 1. one button is for play/stop the melody. other one is for select the melody
#define BUTTON_PIN PINB
#define PLAYBUTTON_PIN 0
#define STOPBUTTON_PIN 0
#define NEXTBUTTON_PIN 1

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

// function to select a melody
void NextMelody()
{
	// check whether the next button is pressed. if so, find the index of the melody
	// index(selectedmelody)    |            melody
	//         0                |   GOT
	//         1                |   Pirates of The Caribbean theme
	//         2                |   Star wars
	//         3                |   Coffin Dance
	//         4                |   Take On Me
	if ( BUTTON_PIN & (1<<NEXTBUTTON_PIN)){
		_delay_ms(debouncing_delay);
		playing += 1;
		selectedmelody = playing % 5;
	}
}

// function to play the selected melody
void playthemelody(int Melody[], int MelodyDuration[], int size)
{
	// melody will play until the stop button is pressed.
	int still_playing = 1;
	while(still_playing){
		for (int x=0; x<size; x++){
			playthenote(Melody[x],MelodyDuration[x]);
			_delay_us(MelodyDuration[x]);
			// check whether the stop button is pressed. if so, stop the melody
			if ( BUTTON_PIN & (1<<STOPBUTTON_PIN)){
				_delay_ms(debouncing_delay);
				still_playing = 0;
				break;
			}
		}
	}
}





#endif /* INCFILE1_H_ */