#ifndef _activity2_h_
#define _activity2_h_

#include "strip.h"

typedef struct
{
	float pos;
	int size;
	int dir;
	float speed;
} activity2_t;

void setupActivity2(strip_t *s, activity2_t data);

#endif
