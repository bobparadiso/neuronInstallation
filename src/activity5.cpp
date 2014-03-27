//Trail, fades red, then pulses and disappears

#include <cstdlib>
#include <string.h>
#include <inttypes.h>

#include "activity5.h"
#include "config.h"
#include "strip.h"
#include "util.h"

//
void Activity5::init()
{
	Activity::init();
	
	//T = 2P / (Vi + Vf)
	//A = (Vf - Vi) * (Vi + Vf) / 2P
	acc = (endVel - startVel) * (startVel + endVel) / (2.0f * (float)colorPos1);
}

//
void Activity5::reset()
{
	dir = 1;
	pos = 0;
	vel = startVel;
	colorT = 0.0f;
	state = 0;
}

//
void Activity5::update(float elapsed)
{
	switch(state)
	{
		case 0: update0(elapsed); break;
		case 1: update1(elapsed); break;
	}
}

//move while fading red
void Activity5::update0(float elapsed)
{
	//grab integer position
	colorT = (float)pos / (float)colorPos1;
	
	colorF_t color = lerpColorF(&c1, &c2, colorT);

	int i, p;
	for (i = 0, p = pos; i < size && p >=0 && p < strip->length; i++, p -= dir)
	{
		uint8_t c = map(i, 0, size - 1, FULL_BRIGHT, 1);
		setPixel(strip->pixels + p, (float)c * color.r, (float)c * color.g, (float)c * color.b);
	}

	//apply vel and acc
	float averageVel = vel + acc * elapsed * 0.5f;
	vel += acc * elapsed;
	if (vel <= 0.0f)
		vel = 0.01f;
	pos += (float)dir * averageVel * elapsed;

	//done
	if (pos > colorPos1)
	{
		colorT = 0.0f;
		state++;
	}
}

//
void Activity5::update1(float elapsed)
{
	colorT += colorVel2 * elapsed;
	if (colorT > 1.0f)
		colorT = 1.0f;
	
	colorF_t color = lerpColorF(&c2, &c3, colorT);

	int i, p;
	for (i = 0, p = pos; i < size && p >=0 && p < strip->length; i++, p -= dir)
	{
		uint8_t c = map(i, 0, size - 1, FULL_BRIGHT, 1);
		setPixel(strip->pixels + p, (float)c * color.r, (float)c * color.g, (float)c * color.b);
	}
	
	//done
	if (colorT == 1.0f)
	{
		reset();
	}
}
