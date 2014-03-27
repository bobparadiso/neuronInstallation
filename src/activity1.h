#ifndef _activity1_h_
#define _activity1_h_

#include "strip.h"

typedef struct
{
	float pos;
	int size;
	int dir;
	float speed;
	float coolDown;
	float clock;
	int state;
} activity1_t;

void setupActivity1(strip_t *s, activity1_t *data);

#endif
