#include <Adafruit_NeoPixel.h>

#define SPEED_PIN A7
#define SIZE_PIN A6

#define LED_PIN1 2
#define NUM_LED1 (60 * 4)

#define LED_PIN2 3
#define NUM_LED2 (60 * 4)

#define LED_PIN3 4
#define NUM_LED3 (60 * 4)

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LED1, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LED2, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LED3, LED_PIN3, NEO_GRB + NEO_KHZ800);

int trailSize = 7;

void setup() {
  Serial.begin(9600);

  strip1.begin();
  strip2.begin();
  strip3.begin();
  
  pinMode(SPEED_PIN, INPUT);
  pinMode(SIZE_PIN, INPUT);
}

long map2(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#define LED_STEP 2

void loop_strip(Adafruit_NeoPixel &strip, int numLED, int &pos, int &dir)
{
    for(int i=0; i<numLED; i++)
    {
      strip.setPixelColor(i, 0);
    }

    for (int i = 0, p = pos; i < trailSize && p >=0 && p < numLED; i++, p -= dir)
    {
      int c;

      if (i <= trailSize/2)
        c = map2(i, 0, trailSize/2, 1, 255);
      else
        c = map2(i, trailSize/2 + 1, trailSize - 1, 255, 1);
        
      strip.setPixelColor(p, c, c, c);
    }

    if (pos == numLED && dir == 1)
      dir = -1;

    if (pos == 0 && dir == -1)
      dir = 1;
      
    pos += dir * LED_STEP;

    strip.show();
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
  static int pos1 = 0;
  static int dir1 = 1;

  static int pos2 = NUM_LED2;
  static int dir2 = -1;

  static int pos3 = 0;
  static int dir3 = 1;
  
  loop_strip(strip1, NUM_LED1, pos1, dir1);
  loop_strip(strip2, NUM_LED2, pos2, dir2);
  loop_strip(strip3, NUM_LED3, pos3, dir3);
  
  updateTrailSize();
  applyDelay();
}
