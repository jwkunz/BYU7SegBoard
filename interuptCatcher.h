/*
  interuptCatcher.h - Moniters the oscilator to trigger an interupt

  Created by Jakob Kunzler 07/04/2018
*/

#ifndef TIMECLOCK_h
#define TIMECLOCK_h

#include "ArduinoStdInt.h"

#define INTERUPTPIN (4)



struct interuptCatcher
{
// States
#define IC_INIT_S 0
#define IC_LOW_S 1
#define IC_HIGH_S 2

  uint8_t currentState = IC_INIT_S;
  uint8_t pin = INTERUPTPIN;
  bool sig_out = false;

  // Settings //

  // Trigger on rising edge (true) or falling edge (false)
  bool riseEdge_flag = true;
  // Trigger on both edges
  bool doubleEdge_flag = false;
} IC;


// If returns true, interupt is occuring
bool interuptCatcher_check4Interupt()
{
  // State Machine for toggles
  switch (IC.currentState) {

    // INIT state
    case IC_INIT_S:

      // No ouput
      IC.sig_out = false;
      // Sense and go to that state
      if (digitalRead(IC.pin))
        IC.currentState = IC_HIGH_S;
      else
        IC.currentState = IC_LOW_S;

      break;

    // LOW state
    case IC_LOW_S:

      // Sense
      if (digitalRead(IC.pin))
      {
        // LOW -> HIGH
        IC.currentState = IC_HIGH_S;

        // Double Edge Case
        if (IC.doubleEdge_flag)
          IC.sig_out = true;
        else
        { // Output based on rising/falling
          if (IC.riseEdge_flag)
            IC.sig_out = true;
          else
            IC.sig_out = false;
        }
      }
      else
      {
        // Stay
        IC.currentState = IC_LOW_S;
        IC.sig_out = false;
      }
      break;

    // HIGH State
    case IC_HIGH_S:

      // Sense
      if (digitalRead(IC.pin))
      {
        // Stay
        IC.currentState = IC_HIGH_S;
        IC.sig_out = false;
      }
      else
      {
        // HIGH -> LOW
        IC.currentState = IC_LOW_S;

        // Double Edge Case
        if (IC.doubleEdge_flag)
          IC.sig_out = true;
        else
        {
          // Output based on rising/falling
          if (IC.riseEdge_flag)
            IC.sig_out = false;
          else
            IC.sig_out = true;
        }
      }
      break;

    // DEFAULT STATE
    default:
      IC.sig_out = false;
      IC.currentState = IC_INIT_S;
      break;
  }


  return IC.sig_out;
}


#endif
