#ifndef globalParameters_h
#define globalParameters_h

// Serial Rate on USB
#define GP_BAUDRATE 9600

// Nominal Interupt Period in micro seconds
#define GB_INTERUPT_PERIOD_US 50000

// Interupts per second
#define GB_INTERUPTS_PER_SECOND (1E6/GB_INTERUPT_PERIOD_US)

// Determined empiracally to tune the clock
/*
// +141 is slow
// +0 is fast#d
// +50 is fast
// +100 is fast
// +104 is fast
// +105 is fast 2 seconds over 15 hours
// +106 is slow 
// +108 is slow 
// +115 is slow
// +128 is slow
*/
#define GB_INTERUPT_TUNE_FACTOR (+106)




#endif
