#ifndef userInterface_h
#define userInterface_h

// Includes
#include "buttonHandler.h"
#include "timeClock.h"
#include "max7221Driver.h"
#include "buttonHandler.h"
#include "buzzerDriver.h"

// General Parameters
#define INTERUPT_PERIOD_US 50000
#define INTERUPTS_PER_SECOND (1E6/INTERUPT_PERIOD_US)
#define DISP_STRING_LEN 10

// Clock Start Parameters
#define START_HOURS 0
#define START_MIN 0
#define START_SEC 0


// State Timing
#define DISP_UPDATE_TICKS (INTERUPTS_PER_SECOND)
#define DISP_FLASH_TICKS (INTERUPTS_PER_SECOND*1/20)

// Saves the display time as timeOnDisplay
void ui_storeDispTime(char* disp_time);

// A debug print
void ui_printDisp(char* dispString);

// Updates the display
void ui_updateDisplay(timePiece* TmPc);

// Checks if the alarm should go
bool ui_checkForAlarmTrigger();

// Tick function for the user interface
void ui_tick();

// Getters //

// Get the alarm status
bool ui_getAlarmStatus();

// Get the ticking status
bool ui_getTickStatus();



#endif
