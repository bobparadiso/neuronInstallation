//Trail, bright in center

#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include "activity1.h"
#include "config.h"
#include "strip.h"
#include "util.h"

#include <Arduino.h>

//
void randomize(activity1_t *activity)
{
	int sizes[] = {5, 10, 20, 50};
	activity->size = sizes[rand() % COUNT_OF(sizes)];
	
	int speeds[] = {15, 30, 60, 100};
	activity->speed = speeds[rand() % COUNT_OF(speeds)];
	
	//Serial.print("speed:");
	//Serial.println(activity->speed);
}

//
void update0(strip_t *s, float elapsed)
{
	activity1_t *trail = (activity1_t *)s->data;

	//grab integer position
	int pos = trail->pos, i, p;

	for (i = 0, p = pos; i < trail->size; i++, p -= trail->dir)
	{
		if (p >=0 && p < s->length)
		{
			uint8_t c;

			if (i < trail->size/2)
				c = map(i, 0, trail->size/2, 1, FULL_BRIGHT);
			else
				c = map(i, trail->size/2, trail->size - 1, FULL_BRIGHT, 1);

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
	activity1_t *activity = (activity1_t *)s->data;

	activity->clock += elapsed;
	if (activity->clock >= activity->coolDown)
	{
		activity->state = 0;
		//if (s->index == 1)
		randomize(activity);
	}
}

//
void runActivity1(strip_t *s, float elapsed)
{
	activity1_t *activity = (activity1_t *)s->data;

	switch(activity->state)
	{
		case 0: update0(s, elapsed); break;
		case 1: update1(s, elapsed); break;
	}
}

//
static void reset(activity1_t *activity)
{
	activity->pos = 0;
	activity->dir = 1;
	activity->state = 0;
	activity->clock = 0.0f;
}

//
void setupActivity1(strip_t *s, activity1_t *data)
{
	s->update = runActivity1;
	s->data = data;

	reset(data);
}
