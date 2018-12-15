#ifndef __INC_MUZIO_COMMON_H
#define __INC_MUZIO_COMMON_H
#include <FastLED.h>
#include "custom.h"

#define LAST_PIXEL_OFFSET N_PIXELS - 1
#define N_PIXELS_HALF (N_PIXELS / 2)

#define SAMPLE_WINDOW 10    // Sample window for average level
#define SAMPLE_WINDOW_2 10  // Sample window for average level
#define PEAK_FALL3 50       //Rate of falling peak dot
#define PEAK_HANG 30        //Time of pause before peak dot falls
#define PEAK_HANG2 40       //Time of pause before peak dot falls
#define PEAK_FALL 30        //Rate of falling peak dot
#define INPUT_FLOOR 10      //Lower range of analogRead input
#define INPUT_CEILING 300   //Max range of analogRead input, the lower the value the more sensitive (1023 = max)300 (150)
#define DC_OFFSET 0         // DC offset in mic signal - if unusure, leave 0
#define NOISE 10            // Noise/hum/interference in mic signal
#define SAMPLES 64          // Length of buffer for dynamic level adjustment
#define SAMPLES2 64         // Length of buffer for dynamic level adjustment
#define TOP (N_PIXELS + 2)  // Allow dot to go slightly off scale
#define SPEED .20           // Amount to increment RGB color by each cycle
#define PEAK_FALL_MILLIS 10 // Rate of peak falling dot
#define FRAMES_PER_SECOND 180
#define POT_PIN 4
#define BG 0

#define COLOR_MIN 0
#define COLOR_MAX 255
#define DRAW_MAX 100
#define SEGMENTS 4           // Number of segments to carve amplitude bar into
#define COLOR_WAIT_CYCLES 10 // Loop cycles to wait between advancing pixel origin
#define qsubd(x, b) ((x > b) ? b : 0)
#define qsuba(x, b) ((x > b) ? x - b : 0) // Analog Unsigned subtraction macro. if result <0, then => 0. By Andrew Tuline.
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

uint8_t volCountLeft = 0; // Frame counter for storing past volume data
int lvlLeft = 10;         // Current "dampened" audio level
int minLvlAvgLeft = 0;    // For dynamic adjustment of graph low & high
int maxLvlAvgLeft = 512;

byte
    peakLeft = 0, // Used for falling dot
    peakRight = 0,
    dotCountLeft = 0,  // Frame counter for delaying dot-falling speed
    dotCountRight = 0, // Frame counter for delaying dot-falling speed
    volCount = 0;      // Frame counter for storing past volume data

int vol[SAMPLES]; // Collection of prior volume samples

CRGB ledsLeft[N_PIXELS];

byte peak = 16;        // Peak level of column; used for falling dots

// Arduino , maximum is 1023
uint16_t volLeft[SAMPLES]; // Collection of prior volume samples

// vu ripple
uint8_t colour;
#define MY_FADE 255 // Starting brightness.
#define MAX_STEPS 16   // Case statement wouldn't allow a variable.
int peakspersec = 0;
int peakcount = 0;

//Samples
#define NSAMPLES 64
unsigned int sample;
unsigned int samplearray[NSAMPLES];
unsigned long samplesum = 0;
unsigned int sampleavg = 0;
int samplecount = 0;
unsigned long oldtime = 0;
unsigned long newtime = 0;

//background color
TBlendType currentBlending;

uint32_t colorToInt(uint8_t r, uint8_t g, uint8_t b);

uint32_t red = colorToInt(255, 0, 0);
// uint32_t orange = colorToInt(255, 127, 0);
// uint32_t yellow = colorToInt(255, 255, 0);
uint32_t green = colorToInt(0, 255, 0);
// uint32_t blue = colorToInt(0, 0, 255);
// uint32_t purple = colorToInt(75, 0, 130);
// uint32_t white = colorToInt(125, 125, 125);

#endif // __INC_MUZIO_COMMON_H