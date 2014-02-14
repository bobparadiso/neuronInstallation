#ifndef _activity5_h_
#define _activity5_h_

#include "strip.h"
#include "util.h"

typedef struct
{
	//config
	int size;
	float startVel;
	float endVel;
	colorF_t c1, c2, c3;
	int colorPos1;
	float colorVel2;

	//state
	float pos;
	int dir;
	float vel;
	float acc;
	float colorT;
	int state;
	
} activity5_t;

void setupActivity5(strip_t *s, activity5_t *data);

#endif
