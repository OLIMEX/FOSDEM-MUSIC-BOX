#include "Arduino.h"
#include "Speaker.h"
#include "Notes.h"
#include <avr/pgmspace.h>

// initializing Timer0 which controls the generated frequency
void Speaker_Init ()
{
  TCCR0A = 0x42;  // COM0B[1:0] = 0b01 --> toggle OC0A on compare match; WGM[1:0] = 0b10 --> CTC
  TCCR0B = 0x0;  // WGM02 = 0; CS[2:0] = 0 --> No clock source (Timer/Counter stopped) page 80
  
  // timer 0 -- OCR0A is TOP of the timer
  //OCR0A = 0xC0;   // OUTPUT_FREQUENCY = CLK/(2*Prescaler*(1+OCR0A))
}

void Speaker_Mute ()
{
  TCCR0B = TCCR0B & 0xF8; // stoping the timer
  TCNT0 = 0;  // reset the counter value
}

// load the OCR0A register and the prescalers based on the desired frequency
void Speaker_Tone (int Frequency)
{
  unsigned long int Value = CLK / Frequency;
  if ((Value>0) && (Value<=256))            // Value [1, 256]; Frequency [31129, 8000000]
  {
    TCCR0B = (TCCR0B & 0xF8) | 0x01;        // Prescaler = 1;
    OCR0A = Value - 1;
  }
  
  //if ((Value>256) && (Value<=256*8))        // Value [257, 2048]; Frequency [3905, 31128]
  if ((Value>256) && (Value<=2048))        // Value [257, 2048]; Frequency [3905, 31128]
  {
    TCCR0B = (TCCR0B & 0xF8) | 0x02;        // Prescaler = 8;
    OCR0A = (Value>>3) - 1;
  }
  
  //if ((Value>256*8) && (Value<=256*64))     // Value [2048, 16384]; Frequency [488, 3904]
  if ((Value>2048) && (Value<=16384))     // Value [2048, 16384]; Frequency [488, 3904]
  {
    TCCR0B = (TCCR0B & 0xF8) | 0x03;        // Prescaler = 64;
    OCR0A = (Value>>6) - 1;
  }
  
  //if ((Value>256*64) && (Value<=256*256))   // Value [16385, 65536]; Frequency [123, 487]
  if ((Value>16384) && (Value<=65536))   // Value [16385, 65536]; Frequency [123, 487]
  {
    TCCR0B = (TCCR0B & 0xF8) | 0x04;        // Prescaler = 256;
    OCR0A = (Value>>8) - 1;
  }
  
  //if ((Value>256*256) && (Value<=256*1024)) // Value [65537, 262144]; Frequency [31, 122]
  if ((Value>65536) && (Value<=262144)) // Value [65537, 262144]; Frequency [31, 122]
  {
    TCCR0B = (TCCR0B & 0xF8) | 0x05;        // Prescaler = 1024; 
    OCR0A = (Value>>10) - 1;
  }
}

// playing a note on the speaker output for the selected duration
void Note (int Speaker_Frequency, int Duration)
{
  // plays the note if it's not a pause note
  if (Speaker_Frequency != _P)
    Speaker_Tone(Speaker_Frequency);
    
  delay(Duration);
  Speaker_Mute ();  //Stop tone on buzzerPin

  delay(20);  // very short silence between the notes to distinguish the equal tones (not to be mistaken with the pauses)
}

// playing series (array) of notes on the two speaker outputs with the specified tempo
// Speaker0_Notes and Speaker1_Notes could differ but the note lengths - Durations should be the same
// in this function all of the input arrays are stored in the PROGMEM section of the memory and thus accessed via pgm_read_word_near function
void Play (const int Channel_Notes[], const int Durations[], int Tempo)
{
  // Current_Note hold the INDEX of the note while Current_Freq hold the FREQUENCY of the note
  int i, Current_Note, Current_Freq, Current_Duration;
  pinMode (SPEAKER, OUTPUT);  // Speaker pin set as output
  for (i=0; ; i++)
  {
    // reading the INDEXES of the notes and the duration of the note (in milliseconds for tempo 60)
    Current_Note = pgm_read_word_near (&Channel_Notes[i]);
    Current_Duration = pgm_read_word_near (&Durations[i]);
    if (Current_Duration == _END)
      break;

    
    #if 0 // this is not mandatory and could be use to transpose a list of tones with certain number up or down
    if (Current_Note != _P)
      Current_Note = Current_Note + 3; // 3 tones higher
    #endif

    // reading the FREQUENCIES of the note
    Current_Freq = pgm_read_word_near (&NoteFrequency[Current_Note]);

    Note(Current_Freq, ((long int)Current_Duration*60)/Tempo);  // sending the frequency and duration to be played
    PORTB = PORTB ^ 0x02; // simple blinking LED after each note
  }
  pinMode (SPEAKER, INPUT); // Speaker pin set as input
}
