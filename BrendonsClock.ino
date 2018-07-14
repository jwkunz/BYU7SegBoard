#include "interupts.h"
#include "timeClock.h"
#include "userInterface.h"

#define PIN_BUZZ 6


void setup() {
  Serial.begin(9600);
  Serial.println("Booted");
  BH_initAll();
  MX_init();
  interupts_init();
}

uint64_t tickCount = 0;
uint32_t lastTime = 0;
uint32_t elapsedTime = 0;
uint32_t timeMark = 0;

void loop() {

  if (BH_getAnIO('B',5))
  {
    Serial.println("Sent ON");
    MX_powerSwitch(true);
    delay(100);
  }
  
  if (BH_getAnIO('B',4))
  {
    Serial.println("Sent OFF");
    MX_powerSwitch(false);
    delay(100);
  }

  if (BH_getAnIO('S',0))
    MX_dispTest(true);
  else
    MX_dispTest(false);
}

void mainISR()
{
  
  // Counter
  tickCount++;
  // Tick Clock
  timeClock_tickFWD();
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

