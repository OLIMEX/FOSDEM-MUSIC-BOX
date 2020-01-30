#include "Arduino.h"
#include "Speaker.h"
#include "Notes.h"
#include <avr/pgmspace.h>

#define VOLUME  // this macros is defined if you want to here the beginning of the notes stronger, used to distinguish 2 consecutive equal notes

// the following variables are used to form the sine (doubled variables for the two channels)
// phaseInc - amount of steps on the sine table to be skipped based on the desired frequency
// phaseReg - the counter in which the phaseInc value is added and summed
// Volume - volume of the sound (it's stronger on the start of the note and gets weaker after that)
// sin - additional variable used for the increased volume at the start of the note
volatile unsigned int phaseInc1, phaseInc2, Volume1, Volume2; 
unsigned int phaseReg1, phaseReg2;
unsigned char sin1, sin2;

volatile unsigned long int Counter=0; // Counter used to measure time (since both timers are used to generate the sine)

// generated sine table from 0 to 255 to determine the duty cycle of the PWM (256 elements total)
const unsigned char SINE_TABLE[]=
{
  128, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159, 162, 165, 168, 171, 174,
  176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211, 213, 216,
  218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 237, 239, 240, 242, 243, 245,
  246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 254, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247,
  246, 245, 243, 242, 240, 239, 237, 236, 234, 232, 230, 228, 226, 224, 222, 220,
  218, 216, 213, 211, 209, 206, 204, 201, 199, 196, 193, 191, 188, 185, 182, 179,
  176, 174, 171, 168, 165, 162, 159, 156, 152, 149, 146, 143, 140, 137, 134, 131,
  127, 124, 121, 118, 115, 112, 109, 106, 103,  99,  96,  93,  90,  87,  84,  81,
   79,  76,  73,  70,  67,  64,  62,  59,  56,  54,  51,  49,  46,  44,  42,  39,
   37,  35,  33,  31,  29,  27,  25,  23,  21,  19,  18,  16,  15,  13,  12,  10,
    9,   8,   7,   6,   5,   4,   3,   3,   2,   1,   1,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   1,   1,   2,   3,   3,   4,   5,   6,   7,   8,
    9,  10,  12,  13,  15,  16,  18,  19,  21,  23,  25,  27,  29,  31,  33,  35,
   37,  39,  42,  44,  46,  49,  51,  54,  56,  59,  62,  64,  67,  70,  73,  76,
   79,  81,  84,  87,  90,  93,  96,  99, 103, 106, 109, 112, 115, 118, 121, 124
};


// interrupt on timer1 compare (should enter every 20us)
ISR(TIMER1_COMPA_vect)
{
  // sum up the current phaseReg with the following phaseInc (which is based on the frequency of the next tone)
  phaseReg1 += phaseInc1;
  phaseReg2 += phaseInc2;
  // get the value from the sine table (since phaseReg is 16 bits we take the high byte
  sin1=SINE_TABLE[(uint8_t)(phaseReg1 >> 8)];
  sin2=SINE_TABLE[(uint8_t)(phaseReg2 >> 8)];
  
#if defined VOLUME
  // increase/decrease the duty cycle of the PWM based on the strength of the sound 
  // shifting of Volume1/2 is with 10 bits instead 8 decrease the volume silencing (otherwise longer notes get silent at the end)
  if (sin1 > 127)
  {
    sin1 -= (Volume1>>10);
    if (sin1 < 127)
      sin1 = 127;
  }
  else
  {
    sin1 += (Volume1>>10);
    if (sin1 > 127)
      sin1 = 127;
  }

  if (sin2 > 127)
  {
    sin2 -= (Volume2>>10);
    if (sin2 < 127)
      sin2 = 127;
  }
  else
  {
    sin2 += (Volume2>>10);
    if (sin2 > 127)
      sin2 = 127;
  }

  if (Volume1<32767)
    Volume1++;
  if (Volume2<32767)
    Volume2++;
#endif 
  OCR0A = (sin1+sin2)/2; // update TC0 output compare register to generate the required duty cycle of the PWM

  Counter++;  // this counter is used for the MyDelay function
}

void PWM_Init ()
{
  pinMode (SPEAKER, OUTPUT);

  // Timer 0
  TCCR0A = 0x83;  // OC0A clear on compare, set at bottom, Fast PWM, page 78
  TCCR0B = 0x01;  // no prescaler
  OCR0A = 0;      // start with duty cycle = 0%

  // Timer 1
  TCCR1 = 0x83 ;  // CTC - clear timer on match A; prescaler = 4, page 89
  OCR1C = (F_CPU / 4 / F_UPDATE - 1); // 79
  TIMSK |= 0x40;  // Timer/Counter1 Output Compare Interrupt Enable

  phaseReg1 = 0;
  phaseReg2 = 0;

  sei();  // Global interrupt enable
}

// loading values into the phaseInc variables used in the interrupt based on the desired frequencies
void Play_Tone (int Freq1, int Freq2)
{
  // load the required frequency into the increment variables
  phaseInc1 = ((long int)Freq1 <<16) / F_UPDATE;  
  phaseInc2 = ((long int)Freq2 <<16) / F_UPDATE;
  Volume1 = 0;
  Volume2 = 0;
}

// custom delay function since the original delay function uses timer1, but since we use it for generating interrupt we should do our own
void MyDelay (volatile unsigned long int Period)  // ms
{
  unsigned long int EndTime = Counter + Period*(F_UPDATE/1000); // 1 cycle in loop is ~20us; 20*50 = 1000us * Period
  while (Counter != EndTime);
}

// Playing two notes at the same time wtih the specified duration
void Note (int Channel0_Frequency, int Channel1_Frequency, int Duration)
{
  Play_Tone (Channel0_Frequency, Channel1_Frequency);
  MyDelay(Duration);
}


// playing series (array) of notes on the two channels of the output with the specified tempo
// Channel0_Notes and Channel1_Notes could differ but the note lengths - Durations should be the same
// in this function all of the input arrays are stored in the PROGMEM section of the memory and thus accessed via pgm_read_word_near function
// the Tempo parameter defines how much quarter notes there will be in a minute and thus making the melody faster or slower
void Play (const int Channel0_Notes[], const int Channel1_Notes[], const int Durations[], int Tempo)
{
  // Current_Note hold the INDEX of the note while Current_Freq hold the FREQUENCY of the note
  int i, C0_Current_Note, C0_Current_Freq, C1_Current_Note, C1_Current_Freq, Current_Duration;
  pinMode (SPEAKER, OUTPUT);  // Speaker pin set as output
  for (i=0; ; i++)
  {
    // reading the INDEXES of the notes and the duration of the note (in milliseconds for tempo 60)
    C0_Current_Note = pgm_read_word_near (&Channel0_Notes[i]);
    C1_Current_Note = pgm_read_word_near (&Channel1_Notes[i]);
    Current_Duration = pgm_read_word_near (&Durations[i]);
    if (Current_Duration == _END) // breaking the cycle when we reach the end of the array
      break;

    
    #if 0 // this is not mandatory and could be use to transpose a list of tones with certain number up or down
    if (C0_Current_Note != _P)
      C0_Current_Note = C0_Current_Note + 12; // one octave up
    if (C1_Current_Note != _P)
      C1_Current_Note = C1_Current_Note - 12; // one octave down
    #endif

    // reading the FREQUENCIES of the note
    C0_Current_Freq = pgm_read_word_near (&NoteFrequency[C0_Current_Note]);
    C1_Current_Freq = pgm_read_word_near (&NoteFrequency[C1_Current_Note]);

    Note(C0_Current_Freq, C1_Current_Freq, ((long int)Current_Duration*60)/Tempo);  // sending the frequencies and duration to be played
    PORTB = PORTB ^ 0x02; // simple blinking LED after each note
  }
  pinMode (SPEAKER, INPUT); // Speaker pin set as input
}
