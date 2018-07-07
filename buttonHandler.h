#ifndef buttonHandler_h
#define buttonHandler_h

#define PIN_BTN_0 2
#define PIN_BTN_1 3
#define PIN_BTN_2 4
#define PIN_BTN_3 5
#define PIN_BTN_4 6
#define PIN_BTN_5 7
#define PIN_SW_0 8

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

// Read all of the buttons
uint8_t BH_readAll()
{
	// Init IO
	uint8_t io = 0;
	// Read Value
	uint8_t read = digitalRead(PIN_SW_0);
	// Shift and add
	io = (io<<1)|read;
	// Repeat...
	read = digitalRead(PIN_BTN_5);
	io = (io<<1)|read;
	read = digitalRead(PIN_BTN_4);
	io = (io<<1)|read;
	read = digitalRead(PIN_BTN_3);
	io = (io<<1)|read;
	read = digitalRead(PIN_BTN_2);
	io = (io<<1)|read;
	read = digitalRead(PIN_BTN_1);
	io = (io<<1)|read;
	read = digitalRead(PIN_BTN_0);
	io = (io<<1)|read;
	// Return the value
	return io;
}




#endif