#ifndef buttonHandler_c
#define buttonHandler_c

#include "buttonHandler.h"

#define BH_NUMIO 6
#define BH_CHARLEN 7

#define BH_VTHRESHOLD 100


// INIT FUNCTION
void BH_initAll()
{
	pinMode(PIN_BTN_0,INPUT);
	pinMode(PIN_BTN_1,INPUT);
	pinMode(PIN_BTN_2,INPUT);
	pinMode(PIN_BTN_3,INPUT);
	pinMode(PIN_BTN_4,INPUT);
	pinMode(PIN_BTN_5,INPUT);
	pinMode(PIN_SW_0,INPUT);
}

// Read an analog IO pin against value BH_VTHRESHOLD
uint8_t _BH_readIO(uint8_t pin)
{
  return(analogRead(pin)>BH_VTHRESHOLD); 
}


// Read all of the buttons, use a mask to pull IO out
uint8_t BH_readAll()
{
	// Init IO
	uint8_t io = 1;
	// Read Value
	uint8_t read = _BH_readIO(PIN_SW_0);
	// Shift and add
	io = (io<<1)|read;
	// Repeat...
	read = _BH_readIO(PIN_BTN_5);
	io = (io<<1)|read;
	read = _BH_readIO(PIN_BTN_4);
	io = (io<<1)|read;
	read = _BH_readIO(PIN_BTN_3);
	io = (io<<1)|read;
	read = _BH_readIO(PIN_BTN_2);
	io = (io<<1)|read;
	read = _BH_readIO(PIN_BTN_1);
	io = (io<<1)|read;
	read = _BH_readIO(PIN_BTN_0);
	io = (io<<1)|read;
	// Return the value
	return io;
}

// Get a particular IO
uint8_t BH_getAnIO(char type, uint8_t index)
{
  if (type == 'S')
  {
    index = BH_NUMIO + index;
  }

  // Shift to the correct bit
  uint8_t numLeft = BH_CHARLEN-index;
  uint8_t IO = (BH_readAll()<<numLeft);
  uint8_t output = IO>>BH_CHARLEN;
  return output;

}

#endif
