/*
  DSP.c++ - Library various DSP functions in C
  
  Created by Jakob Kunzler December 25 2016
*/

#include "DSP.h"

// The sinc function
double dsp_sinc(double x)
{
  if (x == 0)
    return 1;
  else
    return (sin(vPI * x) / (vPI * x));

}

// Makes an inphase (I) mixer
// The amplitude scaling is used to maximize the int storage

void dsp_init_mixerI(double mixerOmega, mixer_t* mixerI, length_t windowLength, uint16_t amplitude)
{
  for (length_t m = 0; m < windowLength; m++)
  {
    mixerI[m] = amplitude*cos(mixerOmega * m);
  }
}

// Makes an quadrature (Q) mixer
// The amplitude scaling is used to maximize the int storage

void dsp_init_mixerQ(double mixerOmega, mixer_t* mixerQ, length_t windowLength, uint16_t amplitude)
{
  for (length_t m = 0; m < windowLength; m++)
  {
    mixerQ[m] = amplitude*sin(mixerOmega * m);
  }
}

// Makes a low pass filter based on a sinc
// The amplitude scaling is used to maximize the int storage

void dsp_init_LPF_sinc(tap_t* taps, length_t numTaps, double cutOff_norm, uint16_t amplitude)
{
  double wC = PI * cutOff_norm;
  for (length_t m = 0; m < numTaps; m++)
  {
    taps[m] = amplitude * (wC / vPI) * dsp_sinc((wC / vPI) * (m - numTaps / 2));
  }
}

// Performs a real only mix with the given mixer

void dsp_realDownMix_window(sample_t* dataWindow, length_t windowLength, mixer_t* mixer, sample_t* downMixed)
{
  for (length_t m = 0; m < windowLength; m++)
  {
    downMixed[m] = dataWindow[m] * mixer[m];
  }
}


// Given I and Q mixer, single side band down mixes and returns complex I and Q results

void dsp_complexDownMix_window(sample_t* dataWindow, length_t windowLength, mixer_t* mixerI, mixer_t* mixerQ, sample_t* downMixedI, sample_t* downMixedQ)
{
  for (length_t m = 0; m < windowLength; m++)
  {
    downMixedI[m] = dataWindow[m] * mixerI[m];
    downMixedQ[m] = dataWindow[m] * mixerQ[m];
  }
}

// A slow but mathematically correct way of filtering IIR
// Takes input data and gives output data


void dsp_filterIIR(tap_t* B,tap_t* A,sample_t* inputData,length_t lengthA, length_t lengthB, length_t dataLength, sample_t* outputData)
{
  // Causal First Term
  tap_t a0 = A[0];
  tap_t b0 = B[0];
  outputData[0] = inputData[0]*b0/a0;

  // Formula
  for(length_t n = 1; n < dataLength; n++)
  {
    double sum = 0;

    for (length_t p = 0; p < dataLength; p++)
    {
      static tap_t b = 0;
      if (p < lengthB)
      {
        b = B[p];
      }
      static tap_t a = 0;
      if (a < lengthA)
      {
        a = A[p];
      }

      int32_t diff = n - p;
      
      static sample_t x = 0;
      if ((diff < dataLength)&&(diff >= 0))
      {
        x = inputData[diff];
      } 
      static sample_t y = 0;
      
      if ((diff < dataLength)&&(diff >= 0))
      {
        y = outputData[diff];
      }

      sum = sum + (b*x) - (a*y);
    }
    outputData[n] = (sample_t)(sum/a0);
  }  
}

// Peforms a polyphase based decimation with the given anti-aliasing filter


void dsp_polyphaseDecimate(sample_t* signal_OG, length_t signal_OG_length, tap_t* filterTaps, length_t filterTaps_length, uint8_t decimationFactor, sample_t* signal_dec, length_t signal_dec_length)
{
  ///////////
  // Poly Phase Decimate
  for (length_t d = 0; d < decimationFactor; d++)
  {
    // Get the signal part
    length_t signalPart_length = signal_dec_length;
    sample_t* signalPart = (sample_t*)calloc(signalPart_length,signalPart_length * sizeof(sample_t));
    for (length_t s = 0; s < signalPart_length; s++)
    {
      length_t index = d + s * decimationFactor;
      // Check if needs to zero pad
      if (index < signal_OG_length)
      {
        signalPart[s] = signal_OG[index];
      }
      else // Effective zero padding
      {
        signalPart[s] = 0;
      }
    }
    // Get the filter part
    length_t filterPart_length = ceil(filterTaps_length / decimationFactor);
    tap_t* filterPart = (tap_t*)calloc(filterPart_length,filterPart_length * sizeof(tap_t));
    for (length_t f = 0; f < filterPart_length; f++)
    {
      length_t index = d + f * decimationFactor;
      // Check if needs to zero pad
      if (index < filterTaps_length)
      {
        filterPart[f] = filterTaps[index];
      }
      else // Effective zero padding
      {
        filterPart[f] = 0;
      }
    }
    // Filter
    sample_t* filterResult = (sample_t*)calloc(signalPart_length,signalPart_length * sizeof(sample_t));
    tap_t* B = filterPart;
    tap_t A[1] = {1};
    // IIR filter acting as FIR
    dsp_filterIIR(B, A, signalPart, 1, filterPart_length, signalPart_length, filterResult);

    // Running Sum
    for (length_t s = 0; s < signalPart_length; s++)
    {
      signal_dec[s] = signal_dec[s] + filterResult[s];
    }

    free(filterPart);
    free(signalPart);
    free(filterResult);
  }
}


double dsp_convert_dB(double x)
{
	return 10*(log10(x));
};

#include "Arduino.h"