#include "Counter1_Channel.h"
#include "Arduino.h"
#include "Speaker.h"

ISR(TIMER1_COMPA_vect) // interrupt vector of Timer/Counter 1 Output Compare A
{
  PORTB = PORTB ^ Speaker_Mask;
}

void Channel1_Init ()
{
  pinMode (SPEAKER, OUTPUT);
  SREG = SREG | 0x80; // I (bit 7) = 1 --> global interrupt enable
  TCCR1 = 0x80;   // CTC1 = 1 --> reset timer on compare match OCR1C; CS1[3:0] = 0 ==> T/C1 stopped  (page 89)
  
  TIMSK = TIMSK | 0x40;   // OCIE1A = 1 --> interrupt on Timer/Counter1 Compare Match A enabled (page 92)

  // timer 1
  // OCR1C holds the Timer/Counter maximum value, i.e. the clear on compare match value. (page 85)
  //OCR1C = 0x00;   // OUTPUT_FREQUENCY = CLK/(2*Prescaler*(1+OCR1C))
}

void Channel1_Mute ()
{
  TCCR1 = TCCR1 & 0xF0; // CS1[3:0] = 0 ==> T/C1 stopped  (page 89)
  TCNT1 = 0;
}

void Channel1_Tone (int Frequency)
{
  unsigned long int Value = CLK / Frequency;
  unsigned char Prescaler = 1;
  
  while (Value > 256)
  {
    Prescaler++;
    Value = Value >> 1;
  }
  OCR1C = Value - 1;
  TCCR1 = (TCCR1 & 0xF0) | Prescaler;
}
