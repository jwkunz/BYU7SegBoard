#include "interupts.h"
#include "timeClock.h"
#include "userInterface.h"

void setup() {
  interupts_init();
  Serial.begin(9600);
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

