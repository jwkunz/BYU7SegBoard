/*
  timeClock.h - Keeps time as a state machine

  Created by Jakob Kunzler 07/04/2018
*/

#ifndef timeClock_c
#define timeClock_c

#include "timeClock.h"

#define SIXTYSECONDS 60
#define SIXTYMINUTES 60
#define MAX_UINT8 255
#define MAX_UINT16 65535
#define TWENTYFOURHOURS 24
#define TWELVEHOURS 12
#define ZERO_UNDERFLOW 0
#define ONETHOUSAND_MS 1000


/* Init the clock

  // tics per second: The number of times to call the tick function before one second passes
  // twelveHour_flag: 12 hour format = true, 24 hour format = false
  // seconds: Initial seconds, 0-59
  // minutes: Initial minutes, 0-59
  // hours: Initial hours in 24 hour format, 0-23
*/
void timeClock_init(timePiece* TmPc,uint16_t ticksPerSec, bool twelveHour_flag, uint8_t seconds, uint8_t minutes, uint8_t hours)
{
  TmPc->twelveHour_flag = twelveHour_flag;
  TmPc->milliSeconds = 0;
  TmPc->seconds = seconds;
  TmPc->minutes = minutes;
  TmPc->hours = hours;
}

// Moves clock forward the given amount
void timeClock_tickFWD(timePiece* TmPc,uint16_t numMilSecs,uint8_t numSecs,uint8_t numMinutes,uint8_t numHours)
{ 
  // Advance Milliseconds
  TmPc->milliSeconds = TmPc->milliSeconds + numMilSecs;
  if (TmPc->milliSeconds >= ONETHOUSAND_MS)
  {
    // Roll Over
    TmPc->milliSeconds = TmPc->milliSeconds%ONETHOUSAND_MS;
    // Advance Seconds
    TmPc->seconds = TmPc->seconds + numSecs;
    if (TmPc->seconds >= SIXTYSECONDS)
    {
      // Roll Over
      TmPc->seconds = TmPc->seconds%SIXTYSECONDS;
      // Advance Minutes
      TmPc->minutes = TmPc->minutes + numMinutes;    
      if (TmPc->minutes >= SIXTYMINUTES)
      {
        // Roll Over
        TmPc->minutes = TmPc->minutes%SIXTYMINUTES;
        // Advance Hours
        TmPc->hours = TmPc->hours + numHours;
        if (TmPc->hours >= TWENTYFOURHOURS)
        {
          // Roll Over
          TmPc->hours = TmPc->hours%TWENTYFOURHOURS;
        }
      }
    }
  }
}

// Move the clock backward the given amount
void timeClock_tickREV(timePiece* TmPc,uint16_t numMilSecs,uint8_t numSecs,uint8_t numMinutes,uint8_t numHours)
{
  // Advance Milliseconds
  TmPc->milliSeconds = TmPc->milliSeconds - numMilSecs;
  if (TmPc->milliSeconds <= 0)
  {
    // Roll Over
    TmPc->milliSeconds = (ONETHOUSAND_MS-(-TmPc->milliSeconds%ONETHOUSAND_MS))%ONETHOUSAND_MS;
    // Advance Seconds
    TmPc->seconds = TmPc->seconds - numSecs;
    if (TmPc->seconds < 0)
    {
      // Roll Over
      TmPc->seconds = (SIXTYSECONDS-(-TmPc->seconds%SIXTYSECONDS))%SIXTYSECONDS;
      // Advance Minutes
      TmPc->minutes = TmPc->minutes - numMinutes;
      if (TmPc->minutes < 0)
      {
        // Roll Over
        TmPc->minutes = (SIXTYMINUTES-(-TmPc->minutes%SIXTYMINUTES))%SIXTYMINUTES;
        // Advance Hours
        TmPc->hours = TmPc->hours - numHours;
        if (TmPc->hours < 0)
        {
          // Roll Over
          TmPc->hours = (TWENTYFOURHOURS-(-TmPc->hours%TWENTYFOURHOURS))%TWENTYFOURHOURS;
        }
      }
    }
  }
}

uint8_t _timeClock_convert24hr_2_12hr(volatile uint8_t hour)
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

char _timeClock_AM_or_PM(volatile uint8_t hour)
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
void _timeClock_updateTime(timePiece* TmPc)
{
  if (TmPc->twelveHour_flag) // 12 Hours
  {
    sprintf(TmPc->currentTime, "%02u:%02u:%02u.%03u %cm", _timeClock_convert24hr_2_12hr(TmPc->hours), TmPc->minutes, TmPc->seconds, TmPc->milliSeconds, _timeClock_AM_or_PM(TmPc->hours));
  }
  else // 24 Hour
  {
    sprintf(TmPc->currentTime, "%02u:%02u:%02u.%03u   ", TmPc->hours, TmPc->minutes, TmPc->seconds, TmPc->milliSeconds);
  }
}

// Copies the current time into time
// time is an array of chars, TIMESTRINGLENGTH long.
void _timeClock_AM_or_PM(timePiece* TmPc,char* timeString)
{
  // Update Time
  _timeClock_updateTime(TmPc);
  // Copy over
  for (uint8_t m = 0; m < TIMESTRINGLENGTH; m++)
  {
    timeString[m] = TmPc->currentTime[m];
  }
}

#endif

