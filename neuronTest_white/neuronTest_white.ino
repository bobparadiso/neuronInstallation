#include <Adafruit_NeoPixel_white.h>

#define LED_PIN A0
#define SPEED_PIN A4
#define PIXELS 60

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel_white strip = Adafruit_NeoPixel_white(PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  pinMode(SPEED_PIN, INPUT);
}

int pos = 0;
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
      strip.setPixelColor(i, c);
    }

    pos = (pos + 1) % PIXELS;
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

