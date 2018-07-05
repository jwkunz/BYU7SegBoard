/*
  DSP.h - Library various DSP functions in C
  
  Created by Jakob Kunzler December 25 2016
*/

#ifndef DSP_h
#define DSP_h

#include <ArduinoStdInt.h>
#include "Arduino.h"

#define vPI 3.14159265359

// TYPES 

// Customize for application memmory needs
// The ideal is double for these three, memmory allowing
typedef double sample_t;
typedef double mixer_t;
typedef double tap_t;

// This is fine
typedef uint16_t length_t;


// The sinc function
double dsp_sinc(double x);

// Makes an inphase (I) mixer
// The amplitude scaling is used to maximize the int storage

void dsp_init_mixerI(double mixerOmega, mixer_t* mixerI, length_t windowLength, uint16_t amplitude);

// Makes an quadrature (Q) mixer
// The amplitude scaling is used to maximize the int storage

void dsp_init_mixerQ(double mixerOmega, mixer_t* mixerQ, length_t windowLength, uint16_t amplitude);

// Makes a low pass filter based on a sinc
// The amplitude scaling is used to maximize the int storage

void dsp_init_LPF_sinc(tap_t* taps, length_t numTaps, double cutOff_norm, uint16_t amplitude);

// Performs a real only mix with the given mixer

void dsp_realDownMix_window(sample_t* dataWindow, length_t windowLength, mixer_t* mixer, sample_t* downMixed);

// Given I and Q mixer, single side band down mixes and returns complex I and Q results

void dsp_complexDownMix_window(sample_t* dataWindow, length_t windowLength, mixer_t* mixerI, mixer_t* mixerQ, sample_t* downMixedI, sample_t* downMixedQ);

// A slow but mathematically correct way of filtering IIR
// Takes input data and gives output data

void dsp_filterIIR(tap_t* B,tap_t* A,sample_t* inputData,length_t lengthA, length_t lengthB, length_t dataLength, sample_t* outputData);

// Peforms a polyphase based decimation with the given anti-aliasing filter

void dsp_polyphaseDecimate(sample_t* signal_OG, length_t signal_OG_length, tap_t* filterTaps, length_t filterTaps_length, uint8_t decimationFactor, sample_t* signal_dec, length_t signal_dec_length);

double dsp_convert_dB(double x);

#endif