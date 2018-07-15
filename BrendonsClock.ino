#include "interupts.h"
#include "timeClock.h"
#include "userInterface.h"
#include "buzzerDriver.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Booted");
  BH_initAll();
  MX_init();
  BZ_init();
  interupts_init();
}

uint64_t tickCount = 0;
uint32_t lastTime = 0;
uint32_t elapsedTime = 0;
uint32_t timeMark = 0;

void loop() {
 
}

void mainISR()
{
  
  // Counter
  tickCount++;
  // Tick Clock if enabled
  if (tickClock_flag)
    timeClock_tickFWD(INTERUPT_PERIOD_S*1000,1,1,1);
  // Tick the User Interface
  ui_tick();
  //printTime();
  //ui_updateDisplay();
  
}


void printTime()
{
  char dispString[TIMESTRINGLENGTH] = {0};
  timeClock_getTime(dispString);
  for(uint8_t m = 0; m < TIMESTRINGLENGTH; m++)
  {
    Serial.print(dispString[m]);
  }
  Serial.println(" ");
}

