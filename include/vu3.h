#ifndef __INC_MUZIO_VU_3_H
#define __INC_MUZIO_VU_3_H
#include <Arduino.h>
#include "common.h"
#include "util.h"

float greenOffset = 30,
      blueOffset = 150;

void vu_centre_rainbow()
{
  uint8_t i;
  uint16_t minLvlLeft, maxLvlLeft;
  int n, height;

  n = readMic(&height);

  greenOffset += SPEED;
  blueOffset += SPEED;
  if (greenOffset >= 255)
    greenOffset = 0;
  if (blueOffset >= 255)
    blueOffset = 0;

  // Color pixels based on rainbow gradient
  for (i = 0; i < N_PIXELS; i++)
  {
    ledsLeft[i] = i >= height ? CRGB::Black : Wheel2(map(i, 0, N_PIXELS - 1, (int)greenOffset, (int)blueOffset));
  }
  // Draw peak dot
  if (peakLeft > 0 && peakLeft <= N_PIXELS - 1)
    ledsLeft[peakLeft] = Wheel2(map(peakLeft, 0, N_PIXELS - 1, 30, 150));

  FastLED.show(); // Update strip

  // Every few frames, make the peak pixel drop by 1:
  if (++dotCountLeft >= PEAK_FALL) //fall rate
  {
    if (peakLeft > 0)
      peakLeft--;
    dotCountLeft = 0;
  }

  volLeft[volCountLeft] = n; // Save sample for dynamic leveling
  if (++volCountLeft >= SAMPLES)
    volCountLeft = 0; // Advance/rollover sample counter

  // Get volume range of prior frames
  minLvlLeft = maxLvlLeft = vol[0];
  for (i = 1; i < SAMPLES; i++)
  {
    if (volLeft[i] < minLvlLeft)
      minLvlLeft = volLeft[i];
    else if (volLeft[i] > maxLvlLeft)
      maxLvlLeft = volLeft[i];
  }

  // minLvl and maxLvl indicate the volume range over prior frames, used
  // for vertically scaling the output graph (so it looks interesting
  // regardless of volume level).  If they're too close together though
  // (e.g. at very low volume levels) the graph becomes super coarse
  // and 'jumpy'...so keep some minimum distance between them (this
  // also lets the graph go to zero when no sound is playing):
  if ((maxLvlLeft - minLvlLeft) < TOP)
    maxLvlLeft = minLvlLeft + TOP;
  minLvlAvgLeft = (minLvlAvgLeft * 63 + minLvlLeft) >> 6; // Dampen min/max levels
  maxLvlAvgLeft = (maxLvlAvgLeft * 63 + maxLvlLeft) >> 6; // (fake rolling average)
}

#endif // __INC_MUZIO_VU_3_H