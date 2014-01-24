//Trail, bright at head

#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include "activity2.h"
#include "config.h"
#include "strip.h"
#include "util.h"

//
void runActivity2(strip_t *s, float elapsed)
{
	activity2_t *trail = (activity2_t *)s->data;

	//grab integer position
	int pos = trail->pos, i, p;

	for (i = 0, p = pos; i < trail->size && p >=0 && p < s->length; i++, p -= trail->dir)
	{
		uint8_t c = map(i, 0, trail->size - 1, FULL_BRIGHT, 1);
		setPixel(s->pixels + p, c, c, c);
	}

	//apply speed
	trail->pos += (float)trail->dir * trail->speed * elapsed;

	//bounce
	if (trail->dir == 1 && trail->pos >= s->length)
	{
		trail->dir = -1;
		trail->pos = s->length;
	}

	//bounce
	if (trail->dir == -1 && trail->pos <= 0)
	{
		trail->dir = 1;
		trail->pos = 0;
	}
}

//
void setupActivity2(strip_t *s, activity2_t data)
{
	s->update = runActivity2;
	s->data = malloc(sizeof(activity2_t));
	memcpy(s->data, &data, sizeof(activity2_t));
}
