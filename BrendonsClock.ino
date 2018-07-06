#include "timeClock.h"
#include "interuptCatcher.h"
#include "max7221Driver.h"

#define INTERUPTS_PER_SECOND 32
#define SCREENUPDATE_TICKOFFSET 8
#define DISP_STRING_LEN 10
#define START_HOURS 12
#define START_MIN 0
#define START_SEC 0
#define TWELVEHOUR_CLK false

void setup() {
  timeClock_init(INTERUPTS_PER_SECOND, TWELVEHOUR_CLK, START_SEC, START_MIN, START_HOURS);
  MX_init();
}

uint64_t tickCount = 0;

void loop() {
  // Wait for interupt
  while(!interuptCatcher_check4Interupt())
  // Counter
  tickCount++;
  // Tick Clock
  timeClock_tickFWD();

  // Update Display every second, with 
  // an offset in tick from the clock tick fwd to spread resources
  if (((tickCount%INTERUPTS_PER_SECOND) - SCREENUPDATE_TICKOFFSET)==0)
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
    dispString[9] = timeString[14];

    // Print Text
    MX_disp_string(dispString,DISP_STRING_LEN);
  }
}
