#ifndef _activity2_h_
#define _activity2_h_

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
} activity2_t;

void setupActivity2(strip_t *s, activity2_t *data);

#endif
