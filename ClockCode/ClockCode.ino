#include "TimerOne.h"
#include "timeClock.h"
#include "userInterface.h"
#include "buzzerDriver.h"
#include "globalParameters.h"

// Time marking variables
uint64_t tickCount = 0;
uint32_t lastTime = 0;
uint32_t elapsedTime = 0;
uint32_t timeMark = 0;

// Init function
void setup() {
  // Begin Serial
  Serial.begin(GP_BAUDRATE);
  // Init the functions
  BH_initAll();
  MX_init();
  BZ_init();
  // Starts the Interupts
  Timer1.initialize(GB_INTERUPT_PERIOD_US+GB_INTERUPT_TUNE_FACTOR);
  Timer1.attachInterrupt(mainISR);
}

// Prints the elapsed time (used in timing tuning)
void printElapsedTime()
{
  timeMark = micros();
  elapsedTime = timeMark-lastTime;
  lastTime = timeMark;
  Serial.println(elapsedTime);
}

// Prints the current time over serial
void printTime(timePiece* TmPc)
{
  char dispString[TC_TIME_LENGTH_STRING] = {0};
  timeClock_getTime(TmPc,dispString);
  for(uint8_t m = 0; m < TC_TIME_LENGTH_STRING; m++)
  {
    Serial.print(dispString[m]);
  }
  Serial.println(" ");
}

// Idle loop
void loop() {
}

// The main interupt routine 
void mainISR()
{
  // Print the elapsed time over Serial
  //printElapsedTime();
  
  // Counter
  tickCount++;
  // Tick Clock if enabled
  if (ui_getTickStatus())
    timeClock_tickFWD(timeClock_getClock(),GB_INTERUPT_PERIOD_US/1000,1,1,1);
  // Tick the User Interface
  ui_tick();

  // Print the current time over Serial
  //printTime(timeClock_getClock()); 
}




