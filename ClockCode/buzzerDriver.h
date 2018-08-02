#ifndef buzzerDriver_h
#define buzzerDriver_h

#include "Arduino.h"
#include "ArduinoStdInt.h"
#include "pinList.h"
#include "globalParameters.h"

#define BZ_BEEP_FREQ_HZ 2000
#define BZ_BEEP_DURATION_MS 100

// BZ_SONG Parameters
#define BZ_BZ_SONG_BPM 120 // BZ_SONG Tempo

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

// Emry's BZ_SONG
const unsigned int BZ_SONG[] = {
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
// End BZ_SONG


#endif
