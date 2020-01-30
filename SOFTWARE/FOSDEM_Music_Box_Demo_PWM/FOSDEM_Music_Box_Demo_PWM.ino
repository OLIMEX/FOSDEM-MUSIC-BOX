#include "Notes.h"
#include "Tracks/All_Tracks.h"
#include "Speaker.h"

// the following functions just call the Play (in Speaker.cpp) function using the notes array from the respective file in "Tracks" folder
// Note: Since not all of them are made polyphonic, for some of them both channels are playing the same! If you want to play polyphonic on them edit the respective file
void Imperial_March ()
{
  Play (IM1_Note, IM1_Note, IM1_Duration, IM1_Tempo);
  Play (IM2_Note, IM2_Note, IM2_Duration, IM2_Tempo);
  Play (IMV1_Note, IMV1_Note, IMV1_Duration, IMV1_Tempo);
  Play (IM2_Note, IM2_Note, IM2_Duration, IM2_Tempo);
  Play (IMV2_Note, IMV2_Note, IMV2_Duration, IMV2_Tempo);
}

void Amazing_Grace ()
{
  Play (AG1_Note, AG1_Note, AG1_Duration, AG1_Tempo);
  Play (AG2_Note, AG2_Note, AG2_Duration, AG2_Tempo);
}

void Mario_Bros_Underwater ()
{
  Play (MBU1_Note, MBU1_Note, MBU1_Duration, MBU1_Tempo);
  Play (MBU2_Note, MBU2_Note, MBU2_Duration, MBU2_Tempo);
  Play (MBU3_Note, MBU3_Note, MBU3_Duration, MBU3_Tempo);
  Play (MBU4_Note, MBU4_Note, MBU4_Duration, MBU4_Tempo);
}

void Silent_Night_Holy_Night ()
{
  Play (SNHN1_Note, SNHN1_Note, SNHN1_Duration, SNHN1_Tempo);
  Play (SNHN2_Note, SNHN2_Note, SNHN2_Duration, SNHN2_Tempo);
  Play (SNHN3_Note, SNHN3_Note, SNHN3_Duration, SNHN3_Tempo);
}

void Test_audio ()
{
  Play (Test1_Note, Test1_Note, Test1_Duration, Test1_Tempo);
}

void Mario_Bros ()
{
  //     Channel0    Channel1
  Play (MB1_NoteC0, MB1_NoteC1, MB1_Duration, MB1_Tempo);
  Play (MB3_NoteC0, MB3_NoteC1, MB3_Duration, MB3_Tempo);
  Play (MB2_NoteC0, MB2_NoteC1, MB2_Duration, MB2_Tempo);
  Play (MB3_NoteC0, MB3_NoteC1, MB3_Duration, MB3_Tempo);
  Play (MB2_NoteC0, MB2_NoteC1, MB2_Duration, MB2_Tempo);
}

void Ode_of_Joy ()
{
  //     Channel0     Channel1
  Play (OOJ1_NoteC1, OOJ1_NoteC2, OOJ1_Duration, OOJ1_Tempo);
  Play (OOJ2_NoteC1, OOJ2_NoteC2, OOJ2_Duration, OOJ2_Tempo);
  Play (OOJ3_NoteC1, OOJ3_NoteC2, OOJ3_Duration, OOJ3_Tempo);
  Play (OOJ4_NoteC1, OOJ4_NoteC2, OOJ4_Duration, OOJ4_Tempo);
}

// at start we are trying to set a "default" value for the photodiode input for the environment and this is the number of samples to take average
#define SAMPLES 20
long int Light_Sensor_Average = 0;  // variable to store the 
int Read_Light_Sensor ()  // reading analog value of the on ADC1 (photodiode)
{
  return analogRead (A1); // A1 --> ADC1 (PB2)
}

void setup()
{
  PWM_Init ();  // initialization of the PWM
  pinMode (1, OUTPUT);  // LED set as output
  // Blinks the LED once to indicate end of the bootloader mode
  digitalWrite (1, HIGH);
  delay (1000);
  digitalWrite (1, LOW);
  // taking the average of the photodiode input to take the average
  for (int i=0; i<SAMPLES; i++)
    Light_Sensor_Average = Light_Sensor_Average + Read_Light_Sensor();
  Light_Sensor_Average = Light_Sensor_Average / SAMPLES;
}

void loop ()
{
  if (Read_Light_Sensor() < Light_Sensor_Average - 0x30)  // if the photodiode sense dimming of the light by a certain value
  {
    // playint any of the tracks
    Mario_Bros ();
    //Ode_of_Joy ();
    //Imperial_March ();
    //Amazing_Grace ();
    //Mario_Bros_Underwater ();
    //Silent_Night_Holy_Night ();
    //Test_audio ();
  }
}
