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

	//apply vel and acc
	float averageVel = trail->vel + trail->acc * elapsed * 0.5f;
	trail->vel += trail->acc * elapsed;
	if (trail->vel <= 0.0f)
		trail->vel = 0.01f;
	trail->pos += (float)trail->dir * averageVel * elapsed;

	//done
	if (trail->pos > trail->colorPos1)
	{
		trail->colorT = 0.0f;
		trail->state++;
	}
}

//
static void reset(activity5_t *activity)
{
	activity->dir = 1;
	activity->pos = 0;
	activity->vel = activity->startVel;
	activity->colorT = 0.0f;
	activity->state = 0;
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
		reset(trail);
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
void setupActivity5(strip_t *s, activity5_t *data)
{
	s->update = runActivity5;
	s->data = data;
	
	//T = 2P / (Vi + Vf)
	//A = (Vf - Vi) * (Vi + Vf) / 2P
	data->acc = (data->endVel - data->startVel) * (data->startVel + data->endVel) / (2.0f * (float)data->colorPos1);
	
	reset(data);
}
