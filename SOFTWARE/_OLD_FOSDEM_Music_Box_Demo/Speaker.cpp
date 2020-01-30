#include "Speaker.h"
#include "Notes.h"
#include "Counter0_Channel.h"
#include "Counter1_Channel.h"
#include <avr/pgmspace.h>

const unsigned char Speaker_Mask = 1<<SPEAKER;

// custom delay function since the default "delay" uses one of the timers which are used for the speaker channel
void MyDelay (volatile long int Time)
{
  volatile long int Divisor;
  while (Time--)
    for (Divisor = 480; Divisor; Divisor--);  // additional cycle to make 1 unit of time ~1ms, not very accurate though
}

// playing a notes on the two channels output (could be the same or different) for the selected duration
void Note (int Channel0_Frequency, int Channel1_Frequency, int Duration)
{
  //Play tone on buzzerPin
  if (Channel0_Frequency != _P)
    Channel0_Tone(Channel0_Frequency);

  if (Channel1_Frequency != _P)
    Channel1_Tone(Channel1_Frequency);
    
  MyDelay(Duration);
  //Stop tone on buzzerPin
  Channel0_Mute ();
  Channel1_Mute ();

  MyDelay(20);  // very short silence between the notes to distinguish the equal tones (not to be mistaken with the pauses)
}

// playing series (array) of notes on the two channels of the output with the specified tempo
// Channel0_Notes and Channel1_Notes could differ but the note lengths - Durations should be the same
// in this function is for arrays stored in the RAM memory
void Play (const int Channel0_Notes[], const int Channel1_Notes[], const int Durations[], int Tempo)
{
  int i;
  for (i=0; Durations[i] != _END; i++)
    Note(Channel0_Notes[i], Channel1_Notes[i], ((long int)Durations[i]*60)/Tempo);
}

// playing series (array) of notes on the two channels of the output with the specified tempo
// Channel0_Notes and Channel1_Notes could differ but the note lengths - Durations should be the same
// in this function all of the input arrays are stored in the PROGMEM section of the memory and thus accessed via pgm_read_word_near function
void Play_PROGMEM (const int Channel0_Notes[], const int Channel1_Notes[], const int Durations[], int Tempo)
{
  int i, C0_Current_Note, C1_Current_Note, Current_Duration;
  for (i=0; ; i++)
  {
    C0_Current_Note = pgm_read_word_near (&Channel0_Notes[i]);
    C1_Current_Note = pgm_read_word_near (&Channel1_Notes[i]);
    Current_Duration = pgm_read_word_near (&Durations[i]);
    if (Current_Duration == _END)
      break;

    Note(C0_Current_Note, C1_Current_Note, ((long int)Current_Duration*60)/Tempo);
  }
}
