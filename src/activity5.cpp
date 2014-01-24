//Trail, fades red, then pulses and disappears

#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include "activity5.h"
#include "config.h"
#include "strip.h"
#include "util.h"

//move while fading red
static void update0(strip_t *s, float elapsed)
{
	activity5_t *trail = (activity5_t *)s->data;

	//grab integer position
	int pos = trail->pos;

	trail->colorT = (float)pos / (float)trail->colorPos1;
	
	colorF_t color = lerpColorF(&trail->c1, &trail->c2, trail->colorT);

	int i, p;
	for (i = 0, p = pos; i < trail->size && p >=0 && p < s->length; i++, p -= trail->dir)
	{
		uint8_t c = map(i, 0, trail->size - 1, FULL_BRIGHT, 1);
		setPixel(s->pixels + p, (float)c * color.r, (float)c * color.g, (float)c * color.b);
	}

	//apply speed
	trail->pos += (float)trail->dir * trail->speed * elapsed;

	//done
	if (trail->pos > trail->colorPos1)
	{
		trail->colorT = 0.0f;
		trail->state++;
	}
}

//
static void update1(strip_t *s, float elapsed)
{
	activity5_t *trail = (activity5_t *)s->data;

	//grab integer position
	int pos = trail->pos;

	trail->colorT += trail->colorVel2 * elapsed;
	if (trail->colorT > 1.0f)
		trail->colorT = 1.0f;
	
	colorF_t color = lerpColorF(&trail->c2, &trail->c3, trail->colorT);

	int i, p;
	for (i = 0, p = pos; i < trail->size && p >=0 && p < s->length; i++, p -= trail->dir)
	{
		uint8_t c = map(i, 0, trail->size - 1, FULL_BRIGHT, 1);
		setPixel(s->pixels + p, (float)c * color.r, (float)c * color.g, (float)c * color.b);
	}
	
	//done
	if (trail->colorT == 1.0f)
	{
		trail->dir = 1;
		trail->pos = 0;
		trail->colorT = 0.0f;
		trail->state = 0;
	}
}


//
void runActivity5(strip_t *s, float elapsed)
{
	activity5_t *trail = (activity5_t *)s->data;

	switch(trail->state)
	{
		case 0: update0(s, elapsed); break;
		case 1: update1(s, elapsed); break;
	}
}

//
void setupActivity5(strip_t *s, activity5_t data)
{
	s->update = runActivity5;
	s->data = malloc(sizeof(activity5_t));
	memcpy(s->data, &data, sizeof(activity5_t));
}
