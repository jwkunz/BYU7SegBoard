#ifndef max7221Driver_h
#define max7221Driver_h

/*
  max7221Driver.h - Communicates with the MAX7721

  Created by Jakob Kunzler 07/04/2018
*/

#include "ArduinoStdInt.h"

// PINS
#define PIN_CS 5
#define PIN_DATA_CLK 4
#define PIN_DATA_IN 2

// Parameters
#define MX_DATA_LEN 16
#define MX_NO_SEGS 8

// Turns on = true, off = false 
void MX_powerSwitch(bool state);

// Sets brightness between 0 and 15
void MX_setBrightness(uint8_t brightness);

// The number of segments to enable (0-7)
void MX_setNoSegments(uint8_t numSegs);

// The number of segments to enable (0-7)
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
