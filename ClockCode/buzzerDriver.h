#ifndef buzzerDriver_h
#define buzzerDriver_h

#include "Arduino.h"
#include "ArduinoStdInt.h"
#include "pinList.h"
#include "globalParameters.h"

#define BZ_BEEP_FREQ_HZ 2000
#define BZ_BEEP_DURATION_MS 100

// BZ_SONG Parameters
#define BZ_SONG_BPM 120 // BZ_SONG Tempo, relative to quarter note

// Beeps quickly
void BZ_beep();

// Simple alarm, drive on or off
void BZ_alarm(bool on);

// Plays BZ_SONG continously while driven on at certain rate (use in a tick function)
void BZ_alarmBZ_SONG(bool on);

// Init the buzzer
void BZ_init();


/// PROGRAM THE MUSIC BELOW


// Notes

#define NOTE_C4 261
#define NOTE_Db4 277
#define NOTE_D4 294
#define NOTE_Eb4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_Gb4 370
#define NOTE_G4 392
#define NOTE_Ab4 415
#define NOTE_A4 440
#define NOTE_Bb4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_Eb5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_Gb5 740
#define NOTE_G5 784
#define NOTE_Ab5 831
#define NOTE_A5 880
#define NOTE_Bb6 932
#define NOTE_B6 988
#define NOTE_C8 1047
#define NOTE_REST 0

// Durations
#define THIRTYSECONDTH_NOTE 1
#define SIXTEENTH_NOTE 2
#define EIGTH_NOTE 4
#define QUARTER_NOTE 8
#define HALF_NOTE 16
#define WHOLE_NOTE 32
#define BREATH_MARK (THIRTYSECONDTH_NOTE)

/* Note on the durations:
In implementation, the fundamental shortest duration is a 32th note,
and each of the other notes are multiples of the 32th note durations.

The tempo beats per minute are scaled to assume a n/4 time signature, ie) 
the quarter note gets the beat.  There are no measures, just notes.

*/

// Emry's BZ_SONG
const unsigned int BZ_SONG[] = 
{ NOTE_REST, BREATH_MARK, // Skip First Note
  NOTE_C4, QUARTER_NOTE,
  NOTE_E4, QUARTER_NOTE,
  NOTE_G4, QUARTER_NOTE,
  NOTE_C5, QUARTER_NOTE,
  NOTE_B4, QUARTER_NOTE,
  NOTE_A4, QUARTER_NOTE,
  NOTE_G4, HALF_NOTE,
  NOTE_REST, BREATH_MARK,
  //
  NOTE_C4, QUARTER_NOTE,
  NOTE_E4, QUARTER_NOTE,
  NOTE_G4, QUARTER_NOTE,
  NOTE_C5, QUARTER_NOTE,
  NOTE_B4, QUARTER_NOTE,
  NOTE_A4, QUARTER_NOTE,
  NOTE_G4, HALF_NOTE,
  NOTE_REST, BREATH_MARK,
  //
  NOTE_C4, QUARTER_NOTE,
  NOTE_E4, QUARTER_NOTE,
  NOTE_G4, QUARTER_NOTE,
  NOTE_C5, QUARTER_NOTE,
  NOTE_E5, QUARTER_NOTE,
  NOTE_D5, QUARTER_NOTE,
  NOTE_E5, QUARTER_NOTE,
  NOTE_G5, QUARTER_NOTE,
  NOTE_E5, QUARTER_NOTE,
  NOTE_D5, QUARTER_NOTE,
  NOTE_C5, WHOLE_NOTE,
  NOTE_REST, BREATH_MARK };
// End BZ_SONG


#endif
