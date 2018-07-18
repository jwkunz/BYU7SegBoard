#ifndef buzzerDriver_h
#define buzzerDriver_h


#define PIN_BUZZER 6
#define INTERUPT_PERIOD_US 50000
#define INTERUPTS_PER_SECOND (1E6/INTERUPT_PERIOD_US)


#define BZ_BEEP_FREQ_HZ 2000
#define BZ_BEEP_DURATION_MS 100
#define BZ_CHIME_DURATION_MS 1000

////////////////////////////////
// Beep
////////////////////////////////
void BZ_beep()
{
  tone(PIN_BUZZER, BZ_BEEP_FREQ_HZ, BZ_BEEP_DURATION_MS);
}

////////////////////////////////
// Defualt Alarm
////////////////////////////////
void BZ_alarm(bool on)
{

  if (on)
    tone(PIN_BUZZER, BZ_BEEP_FREQ_HZ);
  else
    noTone(PIN_BUZZER); 
}


////////////////////////////////
// SONG
////////////////////////////////
#define BZ_SONG_BPM 120 // Not actually scaled, relative to the song programming

static unsigned long sound_lastTickMS = 0; // Last time the tick was called in milliseconds
static unsigned long sound_currentMS = 0; // Current number of milliseconds since program start

unsigned int noteNumber = 0; // Iterator in song array
unsigned int noteBeatsLeft = 0; // Counter of number of beats to hold note.  Counts down to 0.
unsigned int noteFrequency = 0; // Frequency of note to sustain


// Notes
#define C1   261
#define Db1   277
#define D1  294
#define Eb1   311
#define E1   330
#define F1  349
#define Gb1  370
#define G1  392
#define Ab1  415
#define nA1  440
#define Bb1  466
#define nB1   494
#define C2  523
#define D2  587
#define Eb2  622
#define E2   659
#define F2   698
#define Gb2  740
#define G2   784
#define Ab2   831
#define nA2   880
#define Bb2  932
#define nB2   988
#define C3   1047



//Emry
unsigned int SONG[] = {
  0, 0, // Skip First Note
  C1, 1,
  E1, 1,
  G1, 1,
  C2, 1,
  nB1, 1,
  nA1, 1,
  G1, 2,
  //
  C1, 1,
  E1, 1,
  G1, 1,
  C2, 1,
  nB1, 1,
  nA1, 1,
  G1, 2,
  //
  C1, 1,
  E1, 1,
  G1, 1,
  C2, 1,
  E2, 1,
  D2, 1,
  E2, 1,
  G2, 1,
  E2, 2,
  D2, 2,
  C2, 4

};
//
//
// End Song


unsigned int songBytes = sizeof(SONG);
unsigned int songSize = songBytes / (sizeof(unsigned int)); // The length of the song array


// This function sustains the next note of the song until the amound of beats left for that note is zero.
// Each time tickSong is called (every beat) the beat count goes down by 1.
// After finishing a note, it advances to the next note.  It does nothing if the song is finished
// When song is complete, return true

bool BZ_tickSong(unsigned int* song)
{

  if (noteNumber == 0) // Check for Initial State
  {
    // Advance in Array
    noteNumber = noteNumber + 2;
    // Find the intial frequency
    noteFrequency = (song)[noteNumber];
    // Get the initial number of beats
    noteBeatsLeft = (song)[noteNumber + 1];
    return false; // Not Over
  }
  else if (noteNumber >= songSize) // SongOver
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
      noteFrequency = (song)[noteNumber];
      // Get the new number of beats
      noteBeatsLeft = (song)[(noteNumber + 1)];
    }

    return false; // Not Over
  }

}

uint8_t BZ_songTickCounter = 0;
#define BZ_TICKS_PER_BEAT (INTERUPTS_PER_SECOND/(BZ_SONG_BPM/SIXTYSECONDS))

void BZ_alarmSong(bool on)
{

  if (on)
  {
    BZ_songTickCounter++;
    if (BZ_songTickCounter>BZ_TICKS_PER_BEAT)
    {
      if(BZ_tickSong(SONG))
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

void BZ_init()
{
  pinMode(PIN_BUZZER, OUTPUT);
  BZ_beep();
}

#endif
