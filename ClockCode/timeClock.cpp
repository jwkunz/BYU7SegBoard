/*
  timeClock.h - Keeps time as a state machine

  Created by Jakob Kunzler 07/04/2018
*/

#ifndef timeClock_c
#define timeClock_c

#include "timeClock.h"

// Constants for timekeeping
#define TC_SIXTYSECONDS 60
#define TC_SIXTYMINUTES 60
#define TC_TWENTYFOURHOURS 24
#define TC_TWELVEHOURS 12
#define TC_ZERO_UNDERFLOW 0
#define TC_ONETHOUSAND_MS 1000


// Two clocks
timePiece TIME_CLK;
timePiece ALARM_CLK;


/* Init the clock

  // tics per second: The number of times to call the tick function before one second passes
  // twelveHour_flag: 12 hour format = true, 24 hour format = false
  // seconds: Initial seconds, 0-59
  // minutes: Initial minutes, 0-59
  // hours: Initial hours in 24 hour format, 0-23
*/
void timeClock_init(timePiece* TmPc,int16_t ticksPerSec, bool twelveHour_flag, int8_t seconds, int8_t minutes, int8_t hours)
{
  TmPc->twelveHour_flag = twelveHour_flag;
  TmPc->milliSeconds = 0;
  TmPc->seconds = seconds;
  TmPc->minutes = minutes;
  TmPc->hours = hours;
}

// Moves clock forward the given amount
void timeClock_tickFWD(timePiece* TmPc,int16_t numMilSecs,int8_t numSecs,int8_t numMinutes,int8_t numHours)
{ 
  // Advance Milliseconds
  TmPc->milliSeconds = TmPc->milliSeconds + numMilSecs;
  if (TmPc->milliSeconds >= TC_ONETHOUSAND_MS)
  {
    // Roll Over
    TmPc->milliSeconds = TmPc->milliSeconds%TC_ONETHOUSAND_MS;
    // Advance Seconds
    TmPc->seconds = TmPc->seconds + numSecs;
    if (TmPc->seconds >= TC_SIXTYSECONDS)
    {
      // Roll Over
      TmPc->seconds = TmPc->seconds%TC_SIXTYSECONDS;
      // Advance Minutes
      TmPc->minutes = TmPc->minutes + numMinutes;    
      if (TmPc->minutes >= TC_SIXTYMINUTES)
      {
        // Roll Over
        TmPc->minutes = TmPc->minutes%TC_SIXTYMINUTES;
        // Advance Hours
        TmPc->hours = TmPc->hours + numHours;
        if (TmPc->hours >= TC_TWENTYFOURHOURS)
        {
          // Roll Over
          TmPc->hours = TmPc->hours%TC_TWENTYFOURHOURS;
        }
      }
    }
  }
}

// Move the clock backward the given amount
void timeClock_tickREV(timePiece* TmPc,int16_t numMilSecs,int8_t numSecs,int8_t numMinutes,int8_t numHours)
{
  // Advance Milliseconds
  TmPc->milliSeconds = TmPc->milliSeconds - numMilSecs;
  if (TmPc->milliSeconds < TC_ZERO_UNDERFLOW)
  {
    // Roll Over
    TmPc->milliSeconds = (TC_ONETHOUSAND_MS-((-TmPc->milliSeconds)%TC_ONETHOUSAND_MS))%TC_ONETHOUSAND_MS;
    // Advance Seconds
    TmPc->seconds = TmPc->seconds - numSecs;
    if (TmPc->seconds < TC_ZERO_UNDERFLOW)
    {
      // Roll Over
      TmPc->seconds = (TC_SIXTYSECONDS-((-TmPc->seconds)%TC_SIXTYSECONDS))%TC_SIXTYSECONDS;
      // Advance Minutes
      TmPc->minutes = TmPc->minutes - numMinutes;
      if (TmPc->minutes < TC_ZERO_UNDERFLOW)
      {
        // Roll Over
        TmPc->minutes = (TC_SIXTYMINUTES-((-TmPc->minutes)%TC_SIXTYMINUTES))%TC_SIXTYMINUTES;
        // Advance Hours
        TmPc->hours = TmPc->hours - numHours;
        if (TmPc->hours < TC_ZERO_UNDERFLOW)
        {
          // Roll Over
          TmPc->hours = (TC_TWENTYFOURHOURS-((-TmPc->hours)%TC_TWENTYFOURHOURS))%TC_TWENTYFOURHOURS;
        }
      }
    }
  }
}

// Performs conversion on internal 24 hour, to external 12 hour format
uint8_t _timeClock_convert24hr_2_12hr(volatile uint8_t hour)
{
  if(hour == 0)
  {
    return 12;
  }
  if(hour > TC_TWELVEHOURS)
  {
    return hour-TC_TWELVEHOURS;
  }
  return hour;
}

// Decides AM or PM from the 24 hour internal system
char _timeClock_AM_or_PM(volatile uint8_t hour)
{
  if(hour == 0)
  {
    return 'A';
  }
  if(hour >= TC_TWELVEHOURS)
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
// time is an array of chars, TC_TIME_LENGTH_STRING long.
void _timeClock_AM_or_PM(timePiece* TmPc,char* timeString)
{
  // Update Time
  _timeClock_updateTime(TmPc);
  // Copy over
  for (uint8_t m = 0; m < TC_TIME_LENGTH_STRING; m++)
  {
    timeString[m] = TmPc->currentTime[m];
  }
}

// Copies the current time into time
// time is an array of chars, TC_TIME_LENGTH_STRING long.
void timeClock_getTime(timePiece* TmPc,char* timeString)
{
  // Update Time
  _timeClock_updateTime(TmPc);
  // Copy over
  for (uint8_t m = 0; m < TC_TIME_LENGTH_STRING; m++)
  {
    timeString[m] = TmPc->currentTime[m];
  }
}

// Get the alarm pointer
timePiece* timeClock_getAlarm()
{
  return &ALARM_CLK;
};

// Get the main clock pointer
timePiece* timeClock_getClock()
{
  return &TIME_CLK;
};

#endif

