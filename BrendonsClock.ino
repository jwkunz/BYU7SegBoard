#include "interupts.h"
#include "timeClock.h"
#include "userInterface.h"

void setup() {
  interupts_init();
  Serial.begin(9600);
  Serial.println("Preload:");
  Serial.println(INTERUPTS_LOAD);
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
}


