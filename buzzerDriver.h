#ifndef buzzerDriver_h
#define buzzerDriver_h

#include "Arduino.h"
#include "ArduinoStdInt.h"

#define PIN_BUZZER 6
#define INTERUPT_PERIOD_US 50000
#define INTERUPTS_PER_SECOND (1E6/INTERUPT_PERIOD_US)

#define BZ_BEEP_FREQ_HZ 2000
#define BZ_BEEP_DURATION_MS 100
#define BZ_CHIME_DURATION_MS 1000

// Song Parameters
#define BZ_SONG_BPM 120 // Song Tempo
#define BZ_TICKS_PER_BEAT (INTERUPTS_PER_SECOND/(BZ_SONG_BPM/60))

// Beeps quickly
void BZ_beep();

// Simple alarm, drive on or off
void BZ_alarm(bool on);

// Plays song continously while driven on
void BZ_alarmSong(bool on);

// Init the buzzer
void BZ_init();

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



#endif
