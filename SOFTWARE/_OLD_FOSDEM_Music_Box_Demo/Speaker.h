#ifndef	_SPEAKERS_H
#define	_SPEAKERS_H

#define CLK 8000000

#define SPEAKER  0
extern const unsigned char Speaker_Mask;


void MyDelay (volatile long int Time);

void Note (int Channel0_Frequency, int Channel1_Frequency, int Duration);

void Play (const int Channel0_Notes[], const int Channel1_Notes[], const int Durations[], int Tempo);

void Play_PROGMEM (const int Channel0_Notes[], const int Channel1_Notes[], const int Durations[], int Tempo);

#endif
