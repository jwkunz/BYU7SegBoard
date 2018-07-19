#ifndef userInterface_h
#define userInterface_h

// Includes
#include "buttonHandler.h"
#include "timeClock.h"
#include "max7221Driver.h"
#include "buttonHandler.h"
#include "buzzerDriver.h"
#include "globalParameters.h"

// Clock Start Parameters
#define UI_CLK_START_HOURS 0
#define UI_CLK_START_MINUTES 0
#define UI_CLK_START_SECONDS 0

// Twelve Hour Format, or 24 hour?
#define UI_12HR_FLAG (true)

// Alarm Start Parameters
#define UI_ALARM_START_HOURS 5
#define UI_ALARM_START_MINUTES 0
#define UI_ALARM_START_SECONDS 0

// State Timing
#define DISP_UPDATE_TICKS (GB_INTERUPTS_PER_SECOND)
#define DISP_FLASH_TICKS (GB_INTERUPTS_PER_SECOND*1/20)

// Updates the display with data from the time piece
void ui_updateDisplay(timePiece* TmPc);

// Tick function for the user interface
void ui_tick();

// Get the alarm status
bool ui_getAlarmStatus();

// Get the ticking status
bool ui_getTickStatus();



#endif
