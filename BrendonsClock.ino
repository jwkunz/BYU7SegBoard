#include "interuptCatcher.h"
#include "timeClock.h"
#include "userInterface.h"

void setup() {
}

uint64_t tickCount = 0;

void loop() {
  // Wait for interupt
  while(!interuptCatcher_check4Interupt())
  // Counter
  tickCount++;
  // Tick Clock
  timeClock_tickFWD();
  // Tick the User Interface
  ui_tick();
}





