#include "interupts.h"
#include "timeClock.h"
#include "userInterface.h"

#define PIN_BUZZ 6


void setup() {
  interupts_init();
  Serial.begin(9600);
}

uint64_t tickCount = 0;
uint32_t lastTime = 0;
uint32_t elapsedTime = 0;
uint32_t timeMark = 0;

void loop() {

  uint16_t data = 0;
  if (BH_getAnIO('B',0))
  {

    data = _MX_formCode(MX_ADDR_SHUTDOWN,MX_DATA_ON);
    Serial.println(data, BIN);
    _MX_SendData(data);
    delay(2000);

    data = _MX_formCode(MX_ADDR_DISPTEST,MX_DATA_DISPTEST_MODE);
    Serial.println(data, BIN);
    _MX_SendData(data);
    delay(2000);
  }

}

void mainISR()
{
  /*
  // Counter
  tickCount++;
  // Tick Clock
  timeClock_tickFWD();
  // Tick the User Interface
  ui_tick();
  //printTime();
  //ui_updateDisplay();
  */
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

