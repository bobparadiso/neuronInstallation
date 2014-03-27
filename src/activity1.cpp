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
void Activity1::randomize()
{
	int sizes[] = {5, 10, 20, 50};
	size = sizes[rand() % COUNT_OF(sizes)];
	
	int speeds[] = {15, 30, 60, 100};
	speed = speeds[rand() % COUNT_OF(speeds)];
	
	//Serial.print("speed:");
	//Serial.println(speed);
}

//
void Activity1::reset()
{
	pos = 0;
	dir = 1;
	state = 0;
	clock = 0.0f;
}

//
void Activity1::update(float elapsed)
{
	switch(state)
	{
		case 0: update0(elapsed); break;
		case 1: update1(elapsed); break;
	}
}

//
void Activity1::update0(float elapsed)
{
	int i, p;

	for (i = 0, p = pos; i < size; i++, p -= dir)
	{
		if (p >=0 && p < strip->length)
		{
			uint8_t c;

			if (i < size/2)
				c = map(i, 0, size/2, 1, FULL_BRIGHT);
			else
				c = map(i, size/2, size - 1, FULL_BRIGHT, 1);

			setPixel(strip->pixels + p, c, c, c);
		}
	}

	//apply speed
	pos += (float)dir * speed * elapsed;

	//bounce(after delay)
	if (dir == 1 && pos >= strip->length + size)
	{
		dir = -1;
		pos = strip->length;
		clock = 0.0f;
		state++;
	}

	//bounce(after delay)
	if (dir == -1 && pos <= -size)
	{
		dir = 1;
		pos = 0;
		clock = 0.0f;
		state++;
	}
}

//
void Activity1::update1(float elapsed)
{
	clock += elapsed;
	if (clock >= coolDown)
	{
		state = 0;
		//if (strip->index == 1)
		randomize();
	}
}
