#ifndef buttonHandler_h
#define buttonHandler_h

#include "ArduinoStdInt.h"
#include "Arduino.h"

#define PIN_BTN_0 A0
#define PIN_BTN_1 A1
#define PIN_BTN_2 A2
#define PIN_BTN_3 A3
#define PIN_BTN_4 A4
#define PIN_BTN_5 A5
#define PIN_SW_0 A6


// INIT FUNCTION
void BH_initAll();

// Read all of the buttons, use a mask to pull IO out
uint8_t BH_readAll();

// Get a particular IO
uint8_t BH_getAnIO(char type, uint8_t index);


#endif
