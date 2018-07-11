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
#define TWENTYFOURHOURS 24
#define TWELVEHOURS 12
#define TIMESTRINGLENGTH 16
#define ZERO_UNDERFLOW 0
#define ONETHOUSAND_MS 1000

struct timeClock {
  uint16_t ticksPerSec;
  uint16_t msPerTic;
  uint16_t numTicks;
  bool twelveHour_flag;
  uint16_t milliSeconds;
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
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
  TC.ticksPerSec = ticksPerSec;
  TC.msPerTic = 1000 / ticksPerSec;
  TC.twelveHour_flag = twelveHour_flag;
  TC.milliSeconds = 0;
  TC.seconds = seconds;
  TC.minutes = minutes;
  TC.hours = hours;
}

// Call this function at a fixed rate to advance the clock forward

bool timeClock_tickFWD()
{
  // Update flag
  bool secUpdate = false;
  // Update Ticks
  TC.numTicks = TC.numTicks + 1;
  // Milliseconds
  TC.milliSeconds = TC.milliSeconds + TC.msPerTic;

  if (TC.numTicks >= TC.ticksPerSec)
  {
    // Update
    secUpdate = true;
    // Reset
    TC.numTicks = 0;
    TC.milliSeconds = 0;

    // Advance Seconds
    TC.seconds = TC.seconds + 1;
    if (TC.seconds >= SIXTYSECONDS)
    {
      TC.seconds = 0;
      // Advance Minutes
      TC.minutes = TC.minutes + 1;
      if (TC.minutes >= SIXTYMINUTES)
      {
        TC.minutes = 0;
        // Advance Hours
        TC.hours = TC.hours + 1;
        if (TC.hours >= TWENTYFOURHOURS)
        {
          TC.hours = 0;
        }
      }
    }
  }
  return secUpdate;
}

// Call this function at a fixed rate to advance the clock in reverse

bool timeClock_tickREV()
{
  // Update flag
  bool secUpdate = false;
  // Update count
  TC.numTicks = TC.numTicks + 1;
  // Milliseconds
  TC.milliSeconds = TC.milliSeconds - TC.msPerTic;

  if (TC.numTicks >= TC.ticksPerSec)
  {
    // Update
    secUpdate = true;
    // Reset
    TC.numTicks = 0;
    TC.milliSeconds = ONETHOUSAND_MS;

    // Advance Seconds (relies on underflow)
    TC.seconds = TC.seconds - 1;
    if (TC.seconds >= SIXTYSECONDS)
    {
      TC.seconds = SIXTYSECONDS - 1;
      // Advance Minutes (relies on underflow)
      TC.minutes = TC.minutes - 1;
      if (TC.minutes >= SIXTYMINUTES)
      {
        TC.minutes = SIXTYMINUTES - 1;
        // Advance Hours (relies on underflow)
        TC.hours = TC.hours - 1;
        if (TC.hours >= TWENTYFOURHOURS)
        {
          TC.hours = TWENTYFOURHOURS - 1;
        }
      }
    }
  }
return secUpdate;
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

