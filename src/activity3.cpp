//fill in full strip, then empty, wait, restart

#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include "activity3.h"
#include "config.h"
#include "strip.h"
#include "util.h"

//
static void update0(strip_t *s, float elapsed)
{
	activity3_t *activity = (activity3_t *)s->data;

	//grab integer position
	int pos = activity->pos;

	int head = pos;
	int body = head - activity->size;
	int bodySize = s->length - (activity->size * 2);
	int tail = body - bodySize;
	int black = tail - activity->size;

	int i;
	for (i = 0; i < s->length; i++)
	{
		uint8_t c;

		if (i > head)
			c = 0;//ahead of head, so black
		else if (i > body)
			c = map(i - body, 0, activity->size, FULL_BRIGHT, 1);//fade from start of body to start of head
		else if (i > tail)
			c = FULL_BRIGHT;//body is full bright
		else if (i > black)
			c = map(i - black, 0, activity->size, 1, FULL_BRIGHT);//fade from body to tip of tail
		else
			c = 0;

		setPixel(s->pixels + i, c, c, c);
	}

	//apply speed
	activity->pos += activity->speed * elapsed;

	//go to wait
	if (activity->pos >= s->length * 2)
	{
		activity->pos = 0;
		activity->clock = 0.0f;
		activity->state++;
	}
}

//
static void update1(strip_t *s, float elapsed)
{
	activity3_t *activity = (activity3_t *)s->data;

	activity->clock += elapsed;
	if (activity->clock >= activity->coolDown)
		activity->state = 0;
}

//
void runActivity3(strip_t *s, float elapsed)
{
	activity3_t *activity = (activity3_t *)s->data;

	switch(activity->state)
	{
		case 0: update0(s, elapsed); break;
		case 1: update1(s, elapsed); break;
	}
}

//
void setupActivity3(strip_t *s, activity3_t data)
{
	s->update = runActivity3;
	s->data = malloc(sizeof(activity3_t));
	memcpy(s->data, &data, sizeof(activity3_t));
}
