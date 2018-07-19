#ifndef buttonHandler_h
#define buttonHandler_h

#include "ArduinoStdInt.h"
#include "pinList.h"
#include "Arduino.h"

// INIT FUNCTION
void BH_initAll();

// Read all of the buttons, use a mask to pull IO out
uint8_t BH_readAll();

// Get a particular IO
uint8_t BH_getAnIO(char type, uint8_t index);


#endif
