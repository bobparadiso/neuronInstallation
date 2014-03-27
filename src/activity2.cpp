//Trail, bright at head

#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include "activity2.h"
#include "config.h"
#include "strip.h"
#include "util.h"

//
static void update0(strip_t *s, float elapsed)
{
	activity2_t *trail = (activity2_t *)s->data;

	//grab integer position
	int pos = trail->pos, i, p;

	for (i = 0, p = pos; i < trail->size; i++, p -= trail->dir)
	{
		if (p >=0 && p < s->length)
		{
			uint8_t c = map(i, 0, trail->size - 1, FULL_BRIGHT, 1);
			setPixel(s->pixels + p, c, c, c);
		}
	}

	//apply speed
	trail->pos += (float)trail->dir * trail->speed * elapsed;

	//bounce(after delay)
	if (trail->dir == 1 && trail->pos >= s->length + trail->size)
	{
		trail->dir = -1;
		trail->pos = s->length;
		trail->clock = 0.0f;
		trail->state++;
	}

	//bounce(after delay)
	if (trail->dir == -1 && trail->pos <= -trail->size)
	{
		trail->dir = 1;
		trail->pos = 0;
		trail->clock = 0.0f;
		trail->state++;
	}
}

//
static void update1(strip_t *s, float elapsed)
{
	activity2_t *activity = (activity2_t *)s->data;

	activity->clock += elapsed;
	if (activity->clock >= activity->coolDown)
		activity->state = 0;
}

//
void runActivity2(strip_t *s, float elapsed)
{
	activity2_t *activity = (activity2_t *)s->data;

	switch(activity->state)
	{
		case 0: update0(s, elapsed); break;
		case 1: update1(s, elapsed); break;
	}
}

//
static void reset(activity2_t *activity)
{
	activity->pos = 0;
	activity->dir = 1;
	activity->state = 0;
	activity->clock = 0.0f;
}

//
void setupActivity2(strip_t *s, activity2_t *data)
{
	s->update = runActivity2;
	s->data = data;
	
	reset(data);
}
