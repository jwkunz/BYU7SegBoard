/*
  timeClock.h - Keeps time as a state machine

  Created by Jakob Kunzler 07/04/2018
*/

#ifndef timeClock_h
#define timeClock_h

#include "ArduinoStdInt.h"
#include "Arduino.h"

#define TIMESTRINGLENGTH 16
// Data struct for the time clock
// TM is the time clock
// AL is the alarm clock

class timePiece {
  public:
  timePiece()
  {}
  bool twelveHour_flag;
  int16_t milliSeconds;
  int8_t seconds;
  int8_t minutes;
  int8_t hours;
  char currentTime[TIMESTRINGLENGTH];
};


timePiece TIME_CLK;
timePiece ALARM_CLK;

/* Init the clock

  // tics per second: The number of times to call the tick function before one second passes
  // twelveHour_flag: 12 hour format = true, 24 hour format = false
  // seconds: Initial seconds, 0-59
  // minutes: Initial minutes, 0-59
  // hours: Initial hours in 24 hour format, 0-23
*/
void timeClock_init(timePiece* TmPc,uint16_t ticksPerSec, bool twelveHour_flag, uint8_t seconds, uint8_t minutes, uint8_t hours);

// Moves clock forward the given amount
void timeClock_tickFWD(timePiece* TmPc,uint16_t numMilSecs,uint8_t numSecs,uint8_t numMinutes,uint8_t numHours);

// Move the clock backward the given amount
void timeClock_tickREV(timePiece* TmPc,uint16_t numMilSecs,uint8_t numSecs,uint8_t numMinutes,uint8_t numHours);

// Copies the current time into time
// time is an array of chars, TIMESTRINGLENGTH long.
void timeClock_getTime(timePiece* TmPc,char* timeString);

#endif

