#ifndef userInterface_h
#define userInterface_h

// Includes
#include "buttonHandler.h"
#include "timeClock.h"
#include "max7221Driver.h"
#include "buttonHandler.h"
#include "buzzerDriver.h"

// General Parameters
#define INTERUPTS_PER_SECOND (1/INTERUPT_PERIOD_S)
#define DISP_STRING_LEN 10

// Clock Start Parameters
#define START_HOURS 22
#define START_MIN 16
#define START_SEC 35
volatile bool twelveHourClk_flag = true;
volatile bool soundAlarm_flag = false;
volatile bool tickClock_flag = true;


// States
#define UI_INIT_S 0
#define UI_IDLE_S 1
#define UI_DRIVE_ALARM_S 2
#define UI_SET_TIME_SECONDS_S 3
#define UI_SET_TIME_MINUTES_S 4
#define UI_SET_TIME_HOURS_S 5
#define UI_SET_BUTTON_RELEASE_S 6
#define UI_SET_FLASH_S 7

// Button Aliases
#define UI_B0 (BH_getAnIO('B',0))
#define UI_B1 (BH_getAnIO('B',1))
#define UI_B2 (BH_getAnIO('B',2))
#define UI_B3 (BH_getAnIO('B',3))
#define UI_B4 (BH_getAnIO('B',4))
#define UI_B5 (BH_getAnIO('B',5))
#define UI_SW0 (BH_getAnIO('S',0))

// State Timing
#define DISP_UPDATE_TICKS (INTERUPTS_PER_SECOND)
#define DISP_FLASH_TICKS (INTERUPTS_PER_SECOND)


// Counters
uint16_t ui_updateDisp_ctr = 0;
uint16_t ui_flashDisp_ctr = 0;



uint8_t ui_currentState = UI_INIT_S;
uint8_t ui_flashLastState = UI_SET_TIME_SECONDS_S;
uint8_t ui_buttonRelease_NextState = UI_INIT_S;
uint8_t ui_buttonRelease_ButtonNum = 0;

char alarmTime[DISP_STRING_LEN] = {'0', '6', '.', '3', '0', '.', '0', '0', ' ', 'A'};
char timeOnDisplay[DISP_STRING_LEN] = {0};
//////////////////

// Saves the display time as timeOnDisplay
void ui_storeDispTime(char* disp_time)
{
  for (uint8_t m = 0; m < DISP_STRING_LEN; m++)
    timeOnDisplay[m] = disp_time[m];
}


// A debug print
void ui_printDisp(char* dispString)
{
  for (uint8_t m = 0; m < DISP_STRING_LEN; m++)
  {
    Serial.print(dispString[m]);
  }
  Serial.println(" ");
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
    dispString[9] = timeString[13];
  else // Low = 24 hour
    dispString[9] = ' ';


  // Print Text to Seven Segment
  MX_disp_string(dispString, DISP_STRING_LEN);
  // Store Time
  ui_storeDispTime(dispString);


  // DEBUG, Print time
  //ui_printDisp(dispString);
}



// Checks if the alarm should go
bool ui_checkForAlarmTrigger()
{
  // Look for matching characters
  for (uint8_t m = 0; m < DISP_STRING_LEN; m++)
  {
    if (timeOnDisplay[m] != alarmTime[m])
    {
      return false;
    }
  }
  // Check if alarm is set
  uint8_t swVal = BH_getAnIO('S', 0);
  if (swVal == 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}


// Tick function for the user interface
void ui_tick()
{
  // State Machine
  switch (ui_currentState)
  {

    ///////////////////////
    // Intialize everything
    case (UI_INIT_S):
      // Action //
      timeClock_init(INTERUPTS_PER_SECOND, twelveHourClk_flag, START_SEC, START_MIN, START_HOURS);
      ui_updateDisp_ctr = 0;
      tickClock_flag = true;
      // Advance //
      ui_currentState = UI_IDLE_S;
      break;

    ////////////////
    // Waiting state
    case (UI_IDLE_S):
      // Action //
      ui_updateDisp_ctr++;

      // Advance //

      // Set Mode
      if (UI_B5)
      {
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        // Set up the button release parameters
        ui_buttonRelease_ButtonNum = 5;
        ui_buttonRelease_NextState = UI_SET_TIME_SECONDS_S;
        // Stop ticking clock
        tickClock_flag = false;
        Serial.println("Moving to set seconds");
        break;
      }
      // Check for alarm
      if (ui_checkForAlarmTrigger())
      {
        ui_currentState = UI_DRIVE_ALARM_S;
        break;
      }
      // Update Display after so many ticks
      if (ui_updateDisp_ctr >= DISP_UPDATE_TICKS)
      {
        ui_currentState = UI_IDLE_S;
        ui_updateDisplay();
        ui_updateDisp_ctr = 0;
        break;
      }
      break;

    ////////////////
    // Drive Alarm state
    case (UI_DRIVE_ALARM_S):
      // Action //

      // Advance //
      // Check if alarm switch is on
      if (BH_getAnIO('S', 0))
        ui_currentState = UI_DRIVE_ALARM_S;
      else // User turned off
        ui_currentState = UI_IDLE_S;
      break;

    //////////////////////
    // Wait for release
    case (UI_SET_BUTTON_RELEASE_S):
      if (BH_getAnIO('B',ui_buttonRelease_ButtonNum))
      {
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        MX_dispTest(true);
      }
      else
      {
        ui_currentState = ui_buttonRelease_NextState;
        ui_flashDisp_ctr = 0;
        MX_dispTest(false);
      }
      break;

    //////////////////////
    // Set seconds
    case (UI_SET_TIME_SECONDS_S):
      // Action //
      Serial.println("Inside set seconds");

      // Increase
      if (UI_B2)
      {
        timeClock_tickFWD(1000,1,0,0);
        Serial.println("seconds++");
      }
      // Decrease
      else if (UI_B1)
      {
        timeClock_tickREV(1000,1,0,0);
        Serial.println("seconds--");
      }

      // Update Display
      ui_updateDisplay();


      // Advance //

      // Exit Set Mode
      if (UI_B5)
      {
        Serial.println("Leaving to Idle");
        // Set up the button release parameters
        ui_buttonRelease_ButtonNum = 5;
        ui_buttonRelease_NextState = UI_IDLE_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        // Start ticking clock
        tickClock_flag = true;
        break;
      }
      // Left
      if (UI_B3)
      {
        Serial.println("Going to Minutes");
        ui_buttonRelease_ButtonNum = 3;
        ui_buttonRelease_NextState = UI_SET_TIME_MINUTES_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        break;
      }
      // Right
      if (UI_B0)
      {
        Serial.println("Going to Hours");
        ui_buttonRelease_ButtonNum = 0;
        ui_buttonRelease_NextState = UI_SET_TIME_HOURS_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        break;
      }


      // Flash if nothing else
      ui_flashLastState = UI_SET_TIME_SECONDS_S;
      ui_currentState = UI_SET_FLASH_S;
      break;
      
    //////////////////////
    // Set minutes
    case (UI_SET_TIME_MINUTES_S):
      // Action //

      Serial.println("Inside set Minutes");

      // Increase
      if (UI_B2)
      {
        timeClock_tickFWD(1000,60,1,0);
        Serial.println("Minutes++");
      }
      // Decrease
      else if (UI_B1)
      {
        timeClock_tickREV(1000,60,1,0);
        Serial.println("Minutes--");
      }

      // Update Display
      ui_updateDisplay();

      // Advance //

      // Exit Set Mode
      if (UI_B5)
      {
        Serial.println("Leaving to Idle");
        // Set up the button release parameters
        ui_buttonRelease_ButtonNum = 5;
        ui_buttonRelease_NextState = UI_IDLE_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        // Start ticking clock
        tickClock_flag = true;
        break;
      }
      // Left
      if (UI_B3)
      {
        Serial.println("Going to Hours");
        ui_buttonRelease_ButtonNum = 3;
        ui_buttonRelease_NextState = UI_SET_TIME_HOURS_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        break;
      }
      // Right
      if (UI_B0)
      {
        Serial.println("Going to Seconds");
        ui_buttonRelease_ButtonNum = 0;
        ui_buttonRelease_NextState = UI_SET_TIME_SECONDS_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        break;
      }


      // Flash if nothing else
      ui_flashLastState = UI_SET_TIME_MINUTES_S;
      ui_currentState = UI_SET_FLASH_S;
      break;


    //////////////////////
    // Set Hours
    case (UI_SET_TIME_HOURS_S):
      // Action //
      Serial.println("Inside set Hours");

      // Increase
      if (UI_B2)
      {
        timeClock_tickFWD(1000,60,60,1);
        Serial.println("Hours++");
      }
      // Decrease
      else if (UI_B1)
      {
        timeClock_tickREV(1000,60,60,1);
        Serial.println("Hours--");
      }
      // Update
      ui_updateDisplay();

      // Advance //

      // Exit Set Mode
      if (UI_B5)
      {
        Serial.println("Leaving to Idle");
        // Set up the button release parameters
        ui_buttonRelease_ButtonNum = 5;
        ui_buttonRelease_NextState = UI_IDLE_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        // Start ticking clock
        tickClock_flag = true;
        break;
      }
      // Left
      if (UI_B3)
      {
        Serial.println("Going to Seconds");
        ui_buttonRelease_ButtonNum = 3;
        ui_buttonRelease_NextState = UI_SET_TIME_SECONDS_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        break;
      }
      // Right
      if (UI_B0)
      {
        Serial.println("Going to Minutes");
        ui_buttonRelease_ButtonNum = 0;
        ui_buttonRelease_NextState = UI_SET_TIME_MINUTES_S;
        ui_currentState = UI_SET_BUTTON_RELEASE_S;
        break;
      }


      // Flash if nothing else
      ui_flashLastState = UI_SET_TIME_HOURS_S;
      ui_currentState = UI_SET_FLASH_S;
      break;

    //////////////////////
    // MAKE FLASHING
    case (UI_SET_FLASH_S):
      // Action //
      ui_flashDisp_ctr++;
      if(ui_flashDisp_ctr%2)
        MX_writeBLANK();
      else
        ui_updateDisplay();
      // Advance // 
      ui_currentState = ui_flashLastState;
      break;
      
    ///////
    default:
      ui_currentState = UI_INIT_S;
      break;
  }
}




#endif
