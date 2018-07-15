/*
  timeClock.h - Keeps time as a state machine

  Created by Jakob Kunzler 07/04/2018
*/

#ifndef timeClock_h
#define timeClock_h

#include "ArduinoStdInt.h"
#include "Arduino.h"

#define SIXTYSECONDS 60
#define SIXTYMINUTES 60
#define MAX_UINT8 255
#define MAX_UINT16 65535
#define TWENTYFOURHOURS 24
#define TWELVEHOURS 12
#define TIMESTRINGLENGTH 16
#define ZERO_UNDERFLOW 0
#define ONETHOUSAND_MS 1000

struct timeClock {
  bool twelveHour_flag;
  int16_t milliSeconds;
  int8_t seconds;
  int8_t minutes;
  int8_t hours;
  char currentTime[TIMESTRINGLENGTH];

} TC;

/* Init the clock

  // tics per second: The number of times to call the tick function before one second passes
  // twelveHour_flag: 12 hour format = true, 24 hour format = false
  // seconds: Initial seconds, 0-59
  // minutes: Initial minutes, 0-59
  // hours: Initial hours in 24 hour format, 0-23
*/
void timeClock_init(uint16_t ticksPerSec, bool twelveHour_flag, uint8_t seconds, uint8_t minutes, uint8_t hours)
{
  TC.twelveHour_flag = twelveHour_flag;
  TC.milliSeconds = 0;
  TC.seconds = seconds;
  TC.minutes = minutes;
  TC.hours = hours;
}

// Moves clock forward the given amount
void timeClock_tickFWD(uint16_t numMilSecs,uint8_t numSecs,uint8_t numMinutes,uint8_t numHours)
{ 
  // Advance Milliseconds
  TC.milliSeconds = TC.milliSeconds + numMilSecs;
  if (TC.milliSeconds >= ONETHOUSAND_MS)
  {
    // Roll Over
    TC.milliSeconds = TC.milliSeconds%ONETHOUSAND_MS;
    // Advance Seconds
    TC.seconds = TC.seconds + numSecs;
    if (TC.seconds >= SIXTYSECONDS)
    {
      // Roll Over
      TC.seconds = TC.seconds%SIXTYSECONDS;
      // Advance Minutes
      TC.minutes = TC.minutes + numMinutes;
      if (TC.minutes >= SIXTYMINUTES)
      {
        // Roll Over
        TC.minutes = TC.minutes%SIXTYMINUTES;
        // Advance Hours
        TC.hours = TC.hours + numHours;
        if (TC.hours >= TWENTYFOURHOURS)
        {
          // Roll Over
          TC.hours = TC.hours%TWENTYFOURHOURS;
        }
      }
    }
  }
}

// Move the clock backward the given amount
void timeClock_tickREV(uint16_t numMilSecs,uint8_t numSecs,uint8_t numMinutes,uint8_t numHours)
{
  // Advance Milliseconds
  TC.milliSeconds = TC.milliSeconds - numMilSecs;
  if (TC.milliSeconds <= 0)
  {
    // Roll Over
    TC.milliSeconds = (ONETHOUSAND_MS-(-TC.milliSeconds%ONETHOUSAND_MS))%ONETHOUSAND_MS;
    // Advance Seconds
    TC.seconds = TC.seconds - numSecs;
    if (TC.seconds < 0)
    {
      // Roll Over
      TC.seconds = (SIXTYSECONDS-(-TC.seconds%SIXTYSECONDS))%SIXTYSECONDS;
      // Advance Minutes
      TC.minutes = TC.minutes - numMinutes;
      if (TC.minutes < 0)
      {
        // Roll Over
        TC.minutes = (SIXTYMINUTES-(-TC.minutes%SIXTYMINUTES))%SIXTYMINUTES;
        // Advance Hours
        TC.hours = TC.hours - numHours;
        if (TC.hours < 0)
        {
          // Roll Over
          TC.hours = (TWENTYFOURHOURS-(-TC.hours%TWENTYFOURHOURS))%TWENTYFOURHOURS;
        }
      }
    }
  }
}

uint8_t timeClock_convert24hr_2_12hr(uint8_t hour)
{
  if(hour == 0)
  {
    return 12;
  }
  if(hour > TWELVEHOURS)
  {
    return hour-TWELVEHOURS;
  }
  return hour;
}

char timeClock_AM_or_PM(uint8_t hour)
{
  if(hour == 0)
  {
    return 'A';
  }
  if(hour >= TWELVEHOURS)
  {
    return 'P';
  }
  return 'A';
}


// Update Current Time
// By doing this only when called, it save resources
void _timeClock_updateTime()
{
  if (TC.twelveHour_flag) // 12 Hours
  {
    sprintf(TC.currentTime, "%02u:%02u:%02u.%03u %cm", timeClock_convert24hr_2_12hr(TC.hours), TC.minutes, TC.seconds, TC.milliSeconds, timeClock_AM_or_PM(TC.hours));
  }
  else // 24 Hour
  {
    sprintf(TC.currentTime, "%02u:%02u:%02u.%03u   ", TC.hours, TC.minutes, TC.seconds, TC.milliSeconds);
  }
}

// Copies the current time into time
// time is an array of chars, TIMESTRINGLENGTH long.
void timeClock_getTime(char* timeString)
{
  // Update Time
  _timeClock_updateTime();
  // Copy over
  for (uint8_t m = 0; m < TIMESTRINGLENGTH; m++)
  {
    timeString[m] = TC.currentTime[m];
  }
}

#endif

