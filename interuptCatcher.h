/*
  interuptCatcher.h - Moniters the oscilator to trigger an interupt
  
  Created by Jakob Kunzler 07/04/2018
*/

#ifndef TIMECLOCK_h
#define TIMECLOCK_h

#define INTERUPTPIN (4)



struct interuptCatcher
{	
	enum state_t{INIT,LOW,HIGH}
	
	uint8_t pin = INTERUPTPIN;
	state_t currentState = INIT;
	bool sig_out = false;
	bool riseEdge_flag = true;
	bool doubleEdge_flag = false;
	
} IC;


// If returns true, interupt is occuring
bool interuptCatcher_check4Interupt()
{
	// State Machine for toggles
	switch(IC.currentState) {
		
		// INIT state
		case INIT:
		
		// No ouput
		IC.sig_out = false;
		// Sense and go to that state
		if (digitalRead(IC.pin))
			IC.currentState = HIGH;
		else
			IC.currentState = LOW;
			
		break;
		
		// LOW state
		case LOW:
		
		// Sense
		if (digitalRead(IC.pin))
		{
			// LOW -> HIGH
			IC.currentState = HIGH;
			
			// Double Edge Case
			if (doubleEdge_flag)
				IC.sig_out = true;
			else
			{	// Output based on rising/falling
				if (riseEdge_flag)
					IC.sig_out = true;
				else
					IC.sig_out = false;
			}				
		}
		else
		{
			// Stay
			IC.currentState = LOW;
			IC.sig_out = false;
		}		
		break;
		
		// HIGH State
		case HIGH:
		
		// Sense
		if (digitalRead(IC.pin))
		{
			// Stay
			IC.currentState = HIGH;
			IC.sig_out = false;
		}
		else
		{
			// HIGH -> LOW
			IC.currentState = LOW;
			
			// Double Edge Case
			if (doubleEdge_flag)
				IC.sig_out = true;
			else
			{
				// Output based on rising/falling
				if (riseEdge_flag)
					IC.sig_out = false;
				else
					IC.sig_out = true;
			}				
		}	
		break;
		
		// DEFAULT STATE
		default:
			IC.sig_out = false;
			IC.currentState = INIT;
		break;
	}
	
	
	return IC.sig_out;
}


#endif