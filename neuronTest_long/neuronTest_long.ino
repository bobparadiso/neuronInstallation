#include <Adafruit_NeoPixel.h>

#define SPEED_PIN A7
#define SIZE_PIN A6

#define WS2812_PIN 2
#define NUM_WS2812 (60 * 4 * 6)

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel WS2812_strip = Adafruit_NeoPixel(NUM_WS2812, WS2812_PIN, NEO_GRB + NEO_KHZ800);

int trailSize = 7;

void setup() {
  Serial.begin(9600);

  WS2812_strip.begin();
  
  pinMode(SPEED_PIN, INPUT);
  pinMode(SIZE_PIN, INPUT);
}

long map2(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#define LED_STEP 2
void loop_WS2812()
{
    static int pos = 0;
    static int dir = 1;

    for(int i=0; i<NUM_WS2812; i++)
    {
      //WS2812_strip.setPixelColor(i, 0);
    }

    for (int i = 0, p = pos; i < trailSize && p >=0 && p < NUM_WS2812; i++, p -= dir)
    {
      int c;

      if (i <= trailSize/2)
        c = map2(i, 0, trailSize/2, 1, 255);
      else
        c = map2(i, trailSize/2 + 1, trailSize - 1, 255, 1);
        
      WS2812_strip.setPixelColor(p, c, c, c);
    }

    if (pos == NUM_WS2812 && dir == 1)
      dir = -1;

    if (pos == 0 && dir == -1)
      dir = 1;
      
    pos += dir * LED_STEP;

    WS2812_strip.show();
}

void updateTrailSize()
{
  int t = analogRead(SIZE_PIN);
  trailSize = map(t, 0, 1024, 5, 20);
}

void applyDelay()
{
  return;//bptxxx
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

int count = 0;
long lastMillis;
void loop()
{
  loop_WS2812();
  updateTrailSize();
  applyDelay();
  //Serial.println(count++);
  long curMillis = millis();
  Serial.println(curMillis - lastMillis);
  lastMillis = curMillis;
}
