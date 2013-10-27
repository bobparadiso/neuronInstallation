#include "LPD8806.h"
#include "SPI.h"

// Simple test for 160 (5 meters) of LPD8806-based RGB LED strip

/*****************************************************************************/

#define SPEED_PIN A4

// Number of RGB LEDs in strand:
#define NUM_LEDS (32 * 4)

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 3;
int clockPin = 4;

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(NUM_LEDS, dataPin, clockPin);

// You can optionally use hardware SPI for faster writes, just leave out
// the data and clock pin parameters.  But this does limit use to very
// specific pins on the Arduino.  For "classic" Arduinos (Uno, Duemilanove,
// etc.), data = pin 11, clock = pin 13.  For Arduino Mega, data = pin 51,
// clock = pin 52.  For 32u4 Breakout Board+ and Teensy, data = pin B2,
// clock = pin B1.  For Leonardo, this can ONLY be done on the ICSP pins.
//LPD8806 strip = LPD8806(nLEDs);

void setup() {
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}

int pos = 0;
int dir = 1;
int b[] = {255, 150, 100, 50, 25, 5, 1};
//int b[] = {7, 6, 5, 4, 3, 2, 1};
void loop()
{
    for(int i=0; i<NUM_LEDS; i++)
    {
      strip.setPixelColor(i, 0);
    }

    for (int i = pos, j = 0; i >= 0 && j < 7; i--, j++)
    {
      int c = b[j];
      strip.setPixelColor(i, c, c, c);
    }

    if (pos == NUM_LEDS && dir == 1)
      dir = -1;

    if (pos == 0 && dir == -1)
      dir = 1;
      
    pos += dir;

    strip.show();

    int t = analogRead(SPEED_PIN);
    int targetDelay = map(t, 0, 1024, 1000, 5);
    int currentDelay = 0;
    while (currentDelay < targetDelay)
    {
      if (targetDelay - currentDelay < 100)
      {
        delay(targetDelay - currentDelay);
        break;
      }
      
      delay(100);
      currentDelay += 100;

      t = analogRead(SPEED_PIN);
      targetDelay = map(t, 0, 1024, 1500, 5);
    }
}

