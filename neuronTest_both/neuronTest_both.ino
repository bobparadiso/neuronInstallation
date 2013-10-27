#include <Adafruit_NeoPixel.h>
#include "LPD8806.h"
#include "SPI.h"

#define SPEED_PIN A7
#define SIZE_PIN A6

#define WS2812_PIN 2
#define NUM_WS2812 (60 * 4)

#define NUM_LPD8806 (32 * 4)
#define LPD8806_DATA_PIN 3
#define LPD8806_CLOCK_PIN 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel WS2812_strip = Adafruit_NeoPixel(NUM_WS2812, WS2812_PIN, NEO_GRB + NEO_KHZ800);

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 LPD8806_strip = LPD8806(NUM_LPD8806, LPD8806_DATA_PIN, LPD8806_CLOCK_PIN);

int trailSize = 7;

void setup() {
  Serial.begin(9600);

  WS2812_strip.begin();
  LPD8806_strip.begin();
  
  pinMode(SPEED_PIN, INPUT);
  pinMode(SIZE_PIN, INPUT);
}

long map2(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop_WS2812()
{
    static int pos = 0;
    static int dir = 1;

    for(int i=0; i<NUM_WS2812; i++)
    {
      WS2812_strip.setPixelColor(i, 0);
    }

    for (int i = 0, p = pos; i < trailSize && p >=0 && p < NUM_WS2812; i++, p -= dir)
    {
      int c = map2(i, 0, trailSize - 1, 255, 1);
      WS2812_strip.setPixelColor(p, c, c, c);
    }

    if (pos == NUM_WS2812 && dir == 1)
      dir = -1;

    if (pos == 0 && dir == -1)
      dir = 1;
      
    pos += dir;

    WS2812_strip.show();
}

void loop_LPD8806()
{
    static int pos = 0;
    static int dir = 1;

    for(int i=0; i<NUM_LPD8806; i++)
    {
      LPD8806_strip.setPixelColor(i, 0);
    }

    for (int i = 0, p = pos; i < trailSize && p >=0 && p < NUM_LPD8806; i++, p -= dir)
    {
      int c = map2(i, 0, trailSize - 1, 127, 1);
      LPD8806_strip.setPixelColor(p, c, c, c);
    }

    if (pos == NUM_LPD8806 && dir == 1)
      dir = -1;

    if (pos == 0 && dir == -1)
      dir = 1;
      
    pos += dir;

    LPD8806_strip.show();
}

void updateTrailSize()
{
  int t = analogRead(SIZE_PIN);
  trailSize = map(t, 0, 1024, 5, 20);
}

void applyDelay()
{
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

void loop()
{
  loop_WS2812();
  loop_LPD8806();
  updateTrailSize();
  applyDelay();
}
