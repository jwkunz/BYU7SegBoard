#ifndef max7221Driver_h
#define max7221Driver_h

/*
  max7221Driver.h - Communicates with the MAX7721

  Created by Jakob Kunzler 07/04/2018
*/

#include "ArduinoStdInt.h"
#include "pinList.h"

// Parameters
#define MX_NUM_SEGMENTS 8 // Number of segments to use

// Turns on = true, off = false 
void MX_powerSwitch(bool state);

// Sets brightness between 0 and 15
void MX_setBrightness(uint8_t brightness);

// The number of segments to enable (0-7)
void MX_setNoSegments(uint8_t numSegs);

// Do not try and decode the characters for "code B"
void MX_noDecode();

// Toggle display test
void MX_dispTest(bool on);

// Displays the chars in the string on the screen. Handles decimal point
void MX_disp_string(char* text,uint8_t textLength);

// Writes blank data to the screen
void MX_writeBLANK();

// Init Settings
void MX_init();

#endif
