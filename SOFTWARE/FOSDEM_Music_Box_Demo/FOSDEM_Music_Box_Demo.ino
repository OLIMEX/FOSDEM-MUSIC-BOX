#include "Notes.h"
#include "Tracks/All_Tracks.h"
#include "Counter0_Channel.h"
#include "Counter1_Channel.h"
#include "Speaker.h"

// since ATTiny85 has small amount of memory it's better to store the tracks into PROGMEM and the access to these notes is different
// if arrays stored into PROGMEM use the function "Play_PROGMEM", otherwise "Play"
#define PLAY  Play_PROGMEM
//#define PLAY  Play

void Imperial_March ()
{
  PLAY (IM1_Note, IM1_Note, IM1_Duration, IM1_Tempo);
  PLAY (IM2_Note, IM2_Note, IM2_Duration, IM2_Tempo);
  PLAY (IMV1_Note, IMV1_Note, IMV1_Duration, IMV1_Tempo);
  PLAY (IM2_Note, IM2_Note, IM2_Duration, IM2_Tempo);
  PLAY (IMV2_Note, IMV2_Note, IMV2_Duration, IMV2_Tempo);
}

void Amazing_Grace ()
{
  PLAY (AG1_Note, AG1_Note, AG1_Duration, AG1_Tempo);
  PLAY (AG2_Note, AG2_Note, AG2_Duration, AG2_Tempo);
}

void Mario_Bros_Underwater ()
{
  PLAY (MBU1_Note, MBU1_Note, MBU1_Duration, MBU1_Tempo);
  PLAY (MBU2_Note, MBU2_Note, MBU2_Duration, MBU2_Tempo);
  PLAY (MBU3_Note, MBU3_Note, MBU3_Duration, MBU3_Tempo);
  PLAY (MBU4_Note, MBU4_Note, MBU4_Duration, MBU4_Tempo);
}

void Silent_Night_Holy_Night ()
{
  PLAY (SNHN1_Note, SNHN1_Note, SNHN1_Duration, SNHN1_Tempo);
  PLAY (SNHN2_Note, SNHN2_Note, SNHN2_Duration, SNHN2_Tempo);
  PLAY (SNHN3_Note, SNHN3_Note, SNHN3_Duration, SNHN3_Tempo);
}

void Test_audio ()
{
  PLAY (Test1_Note, Test1_Note, Test1_Duration, Test1_Tempo);
}

// polyphonic with one channel 2 octaves lower
void Mario_Bros ()
{
  //     Channel0    Channel1
  PLAY (MB1_NoteC0, MB1_NoteC1, MB1_Duration, MB1_Tempo);
  PLAY (MB3_NoteC0, MB3_NoteC1, MB3_Duration, MB3_Tempo);
  PLAY (MB2_NoteC0, MB2_NoteC1, MB2_Duration, MB2_Tempo);
  PLAY (MB3_NoteC0, MB3_NoteC1, MB3_Duration, MB3_Tempo);
  PLAY (MB2_NoteC0, MB2_NoteC1, MB2_Duration, MB2_Tempo);
}

#define SAMPLES 20
long int Light_Sensor_Average = 0;
int Read_Light_Sensor ()
{
  return analogRead (A1); // A1 --> ADC1 (PB2)
}

void setup()
{
  pinMode (SPEAKER, OUTPUT);
  Channel0_Init ();
  Channel1_Init ();
  //for (int i=0; i<SAMPLES; i++)
    //Light_Sensor_Average = Light_Sensor_Average + Read_Light_Sensor();
  //Light_Sensor_Average = Light_Sensor_Average / SAMPLES;
}


void loop ()
{
  //if (Read_Light_Sensor() < Light_Sensor_Average - 0x30)
  {
    //Mario_Bros ();
    Imperial_March ();
    //Amazing_Grace ();
    //Mario_Bros_Underwater ();
    //Silent_Night_Holy_Night ();
    //Test_audio ();
  }
}
