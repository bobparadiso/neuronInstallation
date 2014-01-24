/** \file
 * Various utility functions
 */
#include <inttypes.h>
#include "util.h"

#include <OctoWS2811.h>
extern OctoWS2811 leds;

//
int map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//
float lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

//
colorF_t lerpColorF(colorF_t *a, colorF_t *b, float t)
{
	colorF_t retval;
	retval.r = lerp(a->r, b->r, t);
	retval.g = lerp(a->g, b->g, t);
	retval.b = lerp(a->b, b->b, t);
	
	return retval;
}

void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue)
{
	leds.setPixel(num, red, green, blue);
}
