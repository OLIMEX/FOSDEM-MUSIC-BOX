#ifndef	_SPEAKERS_H
#define	_SPEAKERS_H

#define F_UPDATE 50000  // This is the DDS update frequency in Hz (NOT the PWM frequency)

#define SPEAKER  0  // pin of the speaker output

void PWM_Init ();

void Play_Tone (int Freq1, int Freq2);

void MyDelay (volatile unsigned long int Period);

void Note (int Channel0_Frequency, int Channel1_Frequency, int Duration);

void Play (const int Channel0_Notes[], const int Channel1_Notes[], const int Durations[], int Tempo);

#endif
