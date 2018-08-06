#ifndef buzzerDriver_c
#define buzzerDriver_c

#include "buzzerDriver.h"

// Beeps quickly
void BZ_beep()
{
  tone(PIN_BUZZER, BZ_BEEP_FREQ_HZ, BZ_BEEP_DURATION_MS);
}

// Simple alarm, drive on or off
void BZ_alarm(bool on)
{

  if (on)
    tone(PIN_BUZZER, BZ_BEEP_FREQ_HZ);
  else
    noTone(PIN_BUZZER); 
}


// Plays BZ_SONG continously while driven on at certain rate (use in a tick function)

static unsigned long sound_lastTickMS = 0; // Last time the tick was called in milliseconds
static unsigned long sound_currentMS = 0; // Current number of milliseconds since program start

unsigned int noteNumber = 0; // Iterator in BZ_SONG array
unsigned int noteBeatsLeft = 0; // Counter of number of beats to hold note.  Counts down to 0.
unsigned int noteFrequency = 0; // Frequency of note to sustain

#define BZ_SONG_NUM_BYTES (sizeof(BZ_SONG)) // Memmory size of the song
#define BZ_SONG_SIZE (BZ_SONG_NUM_BYTES/(sizeof(unsigned int))) // The length of the BZ_SONG array
// Adapted for tempo, the quarter note gets the beat when considering tempo
#define BZ_TICKS_PER_BEAT ((GB_INTERUPTS_PER_SECOND*60)/(BZ_SONG_BPM*QUARTER_NOTE)) 

// This function sustains the next note of the BZ_SONG until the amound of beats left for that note is zero.
// Each time tickBZ_SONG is called (every beat) the beat count goes down by 1.
// After finishing a note, it advances to the next note.  It does nothing if the BZ_SONG is finished
// When BZ_SONG is complete, return true


bool _BZ_tickBZ_SONG(const unsigned int* song)
{
  if (noteNumber == 0) // Check for Initial State
  {
    // Advance in Array
    noteNumber = noteNumber + 2;
    // Find the intial frequency
    noteFrequency = song[noteNumber];
    // Get the initial number of beats
    noteBeatsLeft = song[noteNumber + 1];
    return false; // Not Over
  }
  else if (noteNumber >= BZ_SONG_SIZE) // BZ_SONGOver
  {
    noTone(PIN_BUZZER); // Silence
    return true; // Do nothing
  }
  else // Play Note
  {
    // Decrement the number of beats left
    noteBeatsLeft--;

    if (noteFrequency == 0)
    {
      // Rest Note
      noTone(PIN_BUZZER);

    }
    else
    { // Drive the note
      tone(PIN_BUZZER, noteFrequency);
    }

    // Check to advance
    if (noteBeatsLeft == 0)
    {
      // Advance in Array
      noteNumber = noteNumber + 2;
      // Find the new frequency
      noteFrequency = (BZ_SONG)[noteNumber];
      // Get the new number of beats
      noteBeatsLeft = (BZ_SONG)[(noteNumber + 1)];
    }
    return false; // Not Over
  }

}

// Counts ticks for the tempo
uint8_t BZ_songTickCounter = 0;

// Plays BZ_SONG continously while driven on
void BZ_alarmBZ_SONG(bool on)
{
  if (on)
  {
    BZ_songTickCounter++;
    if (BZ_songTickCounter>BZ_TICKS_PER_BEAT)
    {
      if(_BZ_tickBZ_SONG(BZ_SONG))
      {
        // Reset and repeat
        noteNumber = 0;
        noteBeatsLeft = 0;
        noteFrequency = 0; ;
      }
      BZ_songTickCounter = 0;
    }
  }
  else
    noTone(PIN_BUZZER); 
}

// Init buzzer
void BZ_init()
{
  pinMode(PIN_BUZZER, OUTPUT);
  BZ_songTickCounter = 0;
  BZ_beep();
}

#endif
