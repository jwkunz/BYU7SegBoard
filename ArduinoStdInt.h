/*
  arduinoStdInt.h - Library for the types in <stdint.h> from C
  
  Created by Jakob Kunzler December 25 2016
*/

#ifndef arduinoStdInt_h
#define arduinoStdInt_h

#include "Arduino.h"

// Creates the std_int types for use in Arduino

typedef unsigned char uint8_t; // 1 byte int
typedef unsigned int uint16_t; // 2 byte int
typedef unsigned long uint32_t; // 4 byte int
typedef unsigned long long uint64_t; // 8 byte int

typedef signed char int8_t; // 1 byte int
typedef signed int int16_t; // 2 byte int
typedef signed long int32_t; // 4 byte int
typedef signed long long int64_t; // 8 byte int

#endif
