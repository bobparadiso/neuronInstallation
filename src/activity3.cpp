//fill in full strip, then empty, wait, restart

#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include "activity3.h"
#include "config.h"
#include "strip.h"
#include "util.h"

//
void Activity3::reset()
{
	pos = 0;
	state = 0;
	clock = 0.0f;
}

//
void Activity3::update(float elapsed)
{
	switch(state)
	{
		case 0: update0(elapsed); break;
		case 1: update1(elapsed); break;
	}
}

//
void Activity3::update0(float elapsed)
{
	int head = pos;
	int body = head - size;
	int bodySize = strip->length - (size * 2);
	int tail = body - bodySize;
	int black = tail - size;

	int i;
	for (i = 0; i < strip->length; i++)
	{
		uint8_t c;

		if (i > head)
			c = 0;//ahead of head, so black
		else if (i > body)
			c = map(i - body, 0, size, FULL_BRIGHT, 1);//fade from start of body to start of head
		else if (i > tail)
			c = FULL_BRIGHT;//body is full bright
		else if (i > black)
			c = map(i - black, 0, size, 1, FULL_BRIGHT);//fade from body to tip of tail
		else
			c = 0;

		setPixel(strip->pixels + i, c, c, c);
	}

	//apply speed
	pos += speed * elapsed;

	//go to wait
	if (pos >= strip->length * 2)
	{
		pos = 0;
		clock = 0.0f;
		state++;
	}
}

//
void Activity3::update1(float elapsed)
{
	clock += elapsed;
	if (clock >= coolDown)
		state = 0;
}
