/** \file
 * Utility functions.
 */
#ifndef _util_h_
#define _util_h_

typedef struct
{
  float r, g, b;
} colorF_t;

int map(int x, int in_min, int in_max, int out_min, int out_max);
float lerp(float a, float b, float t);
colorF_t colorFromHex(int hex);
colorF_t lerpColorF(colorF_t *a, colorF_t *b, float t);
void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue);

#endif
