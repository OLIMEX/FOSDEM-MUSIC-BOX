#include "Counter0_Channel.h"
#include "Arduino.h"
#include "Speaker.h"

ISR(TIMER0_COMPA_vect) // interrupt vector of Timer/Counter 0 Output Compare A
{
  PORTB = PORTB ^ Speaker_Mask;
}

void Channel0_Init ()
{
  pinMode (SPEAKER, OUTPUT);
  SREG = SREG | 0x80; // I (bit 7) = 1 --> global interrupt enable
  TCCR0A = 0x02;  // COM0A/B[1:0] = 0b00 --> no toggle on compare match; WGM[1:0] = 0b10 --> CTC
  TCCR0B = 0x0;  // WGM02 = 0; CS[2:0] = 0 --> No clock source (Timer/Counter stopped) (page 80)
  
  TIMSK = TIMSK | 0x10; // OCIE0A = 1    --> interrupt on Timer/Counter0 Compare Match A enabled (page 81)

  // timer 0
  // The OCR0A defines the top value for the counter, hence also its resolution. (Chapter 11.7.2, page 72)
  //OCR0A = 0x00;   // OUTPUT_FREQUENCY = CLK/(2*Prescaler*(1+OCR0A))
}

void Channel0_Mute ()
{
  TCCR0B = TCCR0B & 0xF8;
  TCNT0 = 0;
}

void Channel0_Tone (int Frequency)
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
