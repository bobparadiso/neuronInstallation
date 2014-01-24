#ifndef _activity3_h_
#define _activity3_h_

#include "strip.h"

typedef struct
{
	float pos;
	int size;
	float speed;
	float coolDown;
	float clock;
	int state;
} activity3_t;

void setupActivity3(strip_t *s, activity3_t data);

#endif
