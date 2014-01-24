#ifndef _activity5_h_
#define _activity5_h_

#include "strip.h"
#include "util.h"

typedef struct
{
	float pos;
	int size;
	int dir;
	float speed;
	colorF_t c1, c2, c3;
	float colorT;
	int colorPos1;
	float colorVel2;
	int state;
} activity5_t;

void setupActivity5(strip_t *s, activity5_t data);

#endif
