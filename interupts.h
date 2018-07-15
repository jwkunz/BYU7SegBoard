/*
* Arduino 101: timer and interrupts
* 2: Timer1 overflow interrupt example
* more infos: http://www.letmakerobots.com/node/28278
* created by RobotFreak
*/

// User Parameter 
#define INTERUPT_PERIOD_S (50E-3)
#define INTERUPT_TUNEFACTOR (0) 
//#define INTERUPT_TUNEFACTOR (-128) // Empiracally set for 1 second ticks
// -128 is barely too fast.

// Board Parameters
#define BOARD_CLK_FREQ_HZ 16E6
#define TIMER_PRESCALER 256
#define TIMER_MAX_VALUE (65536)
// Timing Math
#define INTERUPTS_NUM_INCS ((INTERUPT_PERIOD_S*BOARD_CLK_FREQ_HZ)/TIMER_PRESCALER)
#define INTERUPTS_LOAD (TIMER_MAX_VALUE-INTERUPTS_NUM_INCS+INTERUPT_TUNEFACTOR)

 
void interupts_init()
{ 
  // initialize timer1
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
 
  TCNT1 = INTERUPTS_LOAD;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);    // 256 prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

// Put this function in main.c
extern void mainISR();

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = INTERUPTS_LOAD;            // preload timer
  mainISR();
}
 
