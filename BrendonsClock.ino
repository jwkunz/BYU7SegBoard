#include "timeClock.h"
#include "interuptCatcher.h"

void setup() {
	timeClock_init(32,false,0,5,20);
}

void loop() {
	timeClock_tickFWD();
	
}
