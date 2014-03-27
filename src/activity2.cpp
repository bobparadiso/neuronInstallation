//Trail, bright at head

#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include "activity2.h"
#include "config.h"
#include "strip.h"
#include "util.h"

#include <Arduino.h>

//
void Activity2::reset()
{
	pos = 0;
	dir = 1;
	state = 0;
	clock = 0.0f;
}

//
void Activity2::update(float elapsed)
{
	switch(state)
	{
		case 0: update0(elapsed); break;
		case 1: update1(elapsed); break;
	}
}

//
void Activity2::update0(float elapsed)
{
	int i, p;

	for (i = 0, p = pos; i < size; i++, p -= dir)
	{
		if (p >=0 && p < strip->length)
		{
			uint8_t c = map(i, 0, size - 1, FULL_BRIGHT, 1);
			setPixel(strip->pixels + p, c, c, c);
		}
	}

	//apply speed
	pos += (float)dir * speed * elapsed;

	/*
	Serial.print("strip:");
	Serial.print(strip->index);
	Serial.print("  pos:");
	Serial.print(pos);
	Serial.print("  elapsed:");
	Serial.print(elapsed);
	Serial.print("  dir:");
	Serial.print(dir);
	Serial.print("  speed:");
	Serial.println(speed);
	*/

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
void Activity2::update1(float elapsed)
{
	clock += elapsed;
	if (clock >= coolDown)
		state = 0;
}
