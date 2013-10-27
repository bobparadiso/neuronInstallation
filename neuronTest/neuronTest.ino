#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define SPEED_PIN A4
#define PIXELS (60 * 4)

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Serial.println("here");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  pinMode(SPEED_PIN, INPUT);
}

int pos = 0;
int dir = 1;
int b[] = {255, 150, 100, 50, 25, 5, 1};
//int b[] = {7, 6, 5, 4, 3, 2, 1};
void loop()
{
    for(int i=0; i<PIXELS; i++)
    {
      strip.setPixelColor(i, 0);
    }

    for (int i = pos, j = 0; i >= 0 && j < 7; i--, j++)
    {
      int c = b[j];
      strip.setPixelColor(i, c, c, c);
    }

    if (pos == PIXELS && dir == 1)
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

void loop1() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  rainbow(20);
  rainbowCycle(20);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

