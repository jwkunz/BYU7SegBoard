#ifndef userInterface_h
#define userInterface_h

// Includes
#include "buttonHandler.h"
#include "timeClock.h"
#include "max7221Driver.h"
#include "buttonHandler.h"

// General Parameters
#define INTERUPTS_PER_SECOND 32
#define DISP_STRING_LEN 10

// Clock Start Parameters
#define START_HOURS 12
#define START_MIN 0
#define START_SEC 0

// States
#define UI_INIT_S 0
#define UI_IDLE_S 1
#define UI_UPDATE_DISP_S 2
#define UI_START_ALARM_S 3
#define UI_DRIVE_ALARM_S 4

// Button Masks
#define B0_MASK 0x01
#define B1_MASK 0x02
#define B2_MASK 0x04
#define B3_MASK 0x08
#define B4_MASK 0x10
#define B5_MASK 0x20
#define SW0_MASK 0x40

// State Timing
#define DISP_UPDATE_TICKS 16

volatile bool twelveHourClk_flag = false;
volatile bool soundAlarm_flag = false;

uint16_t ui_idle_s_ctr = 0;

uint8_t ui_currentState = UI_INIT_S;

char alarmTime[DISP_STRING_LEN] = {'0','6','.','3','0','.','0','0',' ','A'};
char timeOnDisplay[DISP_STRING_LEN] = {0};
//////////////////

// Saves the display time as timeOnDisplay
void ui_storeDispTime(char* disp_time)
{
  for(uint8_t m=0; m<DISP_STRING_LEN; m++)
    timeOnDisplay[m]=disp_time[m];
}

// Updates the display
void ui_updateDisplay()
{
    // Get the current time
    char timeString[TIMESTRINGLENGTH] = {0};
    timeClock_getTime(timeString);

    // Extract characters
    char dispString[DISP_STRING_LEN] = {0};
    dispString[0] = timeString[0];
    dispString[1] = timeString[1];
    dispString[2] = '.';
    dispString[3] = timeString[3];
    dispString[4] = timeString[4];
    dispString[5] = '.';
    dispString[6] = timeString[6];
    dispString[7] = timeString[7];
    dispString[8] = ' ';

    // Check Format from switch
    if (twelveHourClk_flag) // High =  12 hour
      dispString[9] = timeString[14]; 
    else // Low = 24 hour
      dispString[9] = ' ';
      
    // Print Text to Seven Segment
    MX_disp_string(dispString,DISP_STRING_LEN);
    // Store Time
    ui_storeDispTime(dispString);  
}

// Checks if the alarm should go
bool ui_checkForAlarmTrigger()
{
  // Look for matching characters
  for(uint8_t m=0; m<DISP_STRING_LEN; m++)
  {
    if(timeOnDisplay[m]!=alarmTime[m])
      {
        return true;
      }
  }
  return false;
}


// Tick function for the user interface
void ui_tick()
{
  // State Machine
	switch(ui_currentState)
	{

    ///////////////////////
    // Intialize everything
		case(UI_INIT_S):
		// Action //
    timeClock_init(INTERUPTS_PER_SECOND, twelveHourClk_flag, START_SEC, START_MIN, START_HOURS);
    MX_init();
    BH_initAll();
		ui_idle_s_ctr = 0;
		// Advance //
		ui_currentState = UI_IDLE_S;
		break;

    ////////////////
    // Waiting state
		case(UI_IDLE_S):
		// Action //
		ui_idle_s_ctr++;
		// Advance //

    if (ui_checkForAlarmTrigger())
    {
      ui_currentState = UI_START_ALARM_S;
      break;  
    }
    
    // Update Display after so many ticks
		if (ui_idle_s_ctr >= DISP_UPDATE_TICKS)
		{
			ui_currentState = UI_UPDATE_DISP_S;
      break;
		}
		break;

    ////////////////
    // Start Alarm state
    case(UI_START_ALARM_S):
    // Action //

    // Check if alarm switch is on
    if (BH_readAll()&SW0_MASK)
      soundAlarm_flag = true;
      
    // Advance //
    if (soundAlarm_flag)
      ui_currentState = UI_DRIVE_ALARM_S;
    else
      ui_currentState = UI_IDLE_S;
    break;

    ////////////////
    // Drive Alarm state
    case(UI_DRIVE_ALARM_S):
    // Action //
    soundAlarm_flag = true; 
    // Advance //
    // Check if alarm switch is on
    if (BH_readAll()&SW0_MASK)
      ui_currentState = UI_DRIVE_ALARM_S; 
    else // User turned off
      soundAlarm_flag = false;
      ui_currentState = UI_IDLE_S;     
    break;

    /////////////////
		// Update Display
		case(UI_UPDATE_DISP_S):
		// Action
		ui_updateDisplay();		
		// Advance
		ui_currentState = UI_IDLE_S;		
		break;
		
		///////
		default:
		ui_currentState = UI_INIT_S;
		break;
	}
}





#endif
