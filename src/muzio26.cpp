#include <Arduino.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
#include <Bounce2.h>
#include "common.h"
#include "vu0.h"
#include "vu1.h"
#include "vu2.h"
#include "vu3.h"
#include "vu5.h"
#include "vu6.h"
#include "vu7.h"
#include "vu8.h"
#include "vu9.h"
#include "vu10.h"
#include "vu11.h"
#include "vu12.h"
#include "vu13.h"
#include "vu14.h"
#include "vu15.h"
#include "vu16.h"

// Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

uint16_t dist;    // A random number for noise generator.
uint16_t scale = 30;     // Wouldn't recommend changing this on the fly, or the animation will be really blocky.

const int buttonPin = 4; // the number of the pushbutton pin

Bounce debouncer = Bounce(); // Instantiate a Bounce object

//typedef struct __attribute((__packed__)) PVu 
typedef struct PVu
{
  const uint8_t id;
  void (*pattern)();
} PVu;

//Variables will change:
uint8_t buttonPushCounter = 0; // counter for the number of button presses
uint8_t demoCurPatternNumber = 1; // Index number of which pattern is current. We skip All2.

// Prototype
void All2();

#ifdef MUZIO_DEBUG
void displayPattern(uint8_t patternNumber);

const char s0[] PROGMEM = "Demo"; // "String 0" etc are strings to store - change to suit.
const char s1[] PROGMEM = "Normal Centre out";
const char s2[] PROGMEM = "Rainbow Normal";
const char s3[] PROGMEM = "Blue, green dots";
const char s4[] PROGMEM = "Centre rainbow";
const char s5[] PROGMEM = "Not Yet Implemented";
const char s6[] PROGMEM = "Shooting star";
const char s7[] PROGMEM = "Red dots";
const char s8[] PROGMEM = "Ripple";
const char s9[] PROGMEM = "Shatter";
const char s10[] PROGMEM = "Pulse";
const char s11[] PROGMEM = "Red centre, blue dots";
const char s12[] PROGMEM = "Juggle";
const char s13[] PROGMEM = "Half peak blue dots";
const char s14[] PROGMEM = "Not Yet Implemented";
const char s15[] PROGMEM = "White red dots";
const char s16[] PROGMEM = "Classic normal";
const char s17[] PROGMEM = "Classic centre";
const char s18[] PROGMEM = "Not Yet Implemented";
const char s19[] PROGMEM = "Not Yet Implemented";

const char *const string_table[] PROGMEM = {
    s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19};
#endif

/**
 * Basic struct with an index to point out the name in flash mem array
 * and a function  pointer on a vu pattern.
 * 
 */
static PVu allPatterns[] = {
    {0, All2},
    {1, vu_normal_center_out},
    {2, vu_rainbow_normal},
    {3, vu_blue_green_dots},
    {4, vu_centre_rainbow},
    {6, vu_shooting_star},
    {7, vu_red_dots},
    {8, vu_ripple},
    {9, vu_shatter},
    {10, vu_pulse},
    {11, vu_red_centre_blue_dots},
    {12, vu_juggle},
    {13, vu_half_peak_blue_dots},
    {15, vu_white_red_dots},
    {16, vu_classic_normal},
    {17, vu_classic_centre}};

void setup()
{
  analogReference(EXTERNAL);
  currentBlending = LINEARBLEND;
  Serial.begin(115200);

  debouncer.attach(buttonPin, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncer.interval(25);                    // Use a debounce interval of 25 milliseconds

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(ledsLeft, N_PIXELS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  currentPalette = CRGBPalette16(CRGB::Black);
  targetPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  dist = random16(12345); // A semi-random number for our noise generator

  // switch off all leds
  FastLED.clear(true);
}

void printPattern(uint8_t idx)
{
  char buffer[30];
  int idxName = allPatterns[idx].id;
  strcpy_P(buffer, (char *)pgm_read_word(&(string_table[idxName]))); // Necessary casts and dereferencing, just copy.
  Serial.print(F("Demo Pattern id: "));
  Serial.print(idxName);
  Serial.print(F(", name: "));
  Serial.println(buffer);
}

void loop()
{
  debouncer.update();   // Update the Bounce instance
  if (debouncer.fell()) // Call code if button transitions from HIGH to LOW
  {
    buttonPushCounter++;
    if (buttonPushCounter >= ARRAY_SIZE(allPatterns))
    {
      buttonPushCounter = 0;
      demoCurPatternNumber = 1;
    }

    if (MUZIO_DEBUG)
    {
      printPattern(buttonPushCounter);
      if (buttonPushCounter == 0)
      {
        printPattern(demoCurPatternNumber);
      }
    }

    // short visual effect to display which patter is applied now.
    displayPattern(buttonPushCounter);
  }
  // Call current pattern
  allPatterns[buttonPushCounter].pattern();
}


// while displaying pattern button isn ot working any more
// If you want to be able to ... you have to use interuption.
void displayPattern(uint8_t patternNumber)
{
  FastLED.clear(true);
  if (patternNumber == 0) // protection
  {
    patternNumber = N_PIXELS;
  }

  for (int j = 0; j < patternNumber; j++)
  {
    ledsLeft[j] = CRGB::Red;
  }

  FastLED.show();
  delay(100);
  for (int j = 0; j < 10; j++)
  {
    ledsLeft[patternNumber - 1] = CRGB::Red;
    FastLED.delay(70);
    ledsLeft[patternNumber - 1] = CRGB::Black;
    FastLED.delay(70);
  }
  FastLED.clear(true);
}

void nextPatternAuto()
{
  // add one to the current pattern number, and wrap around at the end
  demoCurPatternNumber++;
  demoCurPatternNumber = demoCurPatternNumber >= ARRAY_SIZE(allPatterns) ? 1 : demoCurPatternNumber;
  FastLED.showColor(CRGB::Black);
  if (MUZIO_DEBUG)
  {
    printPattern(demoCurPatternNumber);
  }
}

void All2()
{
  // Call the current pattern function once, updating the 'leds' array
  allPatterns[demoCurPatternNumber].pattern();
  EVERY_N_SECONDS(30)
  {
    nextPatternAuto(); // change patterns periodically
  }
}

