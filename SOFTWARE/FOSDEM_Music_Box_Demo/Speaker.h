#ifndef	_SPEAKER_H
#define	_SPEAKER_H

#define CLK 8000000

#define SPEAKER  0

void Speaker_Init ();

void Speaker_Mute ();

void Speaker_Tone (int Frequency);

void MyDelay (volatile long int Time);

void Note (int Speaker_Frequency, int Duration);

void Play (const int Channel_Notes[], const int Durations[], int Tempo);

#endif
