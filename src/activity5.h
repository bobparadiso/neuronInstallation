#ifndef _activity5_h_
#define _activity5_h_

#include "activity.h"
#include "util.h"

class Activity5 : public Activity
{
public:
	//config
	int size;
	float startVel;
	float endVel;
	colorF_t c1, c2, c3, c4;
	int stopPos;
	float colorVel3, colorVel4;

	//state
	float pos;
	int dir;
	float vel;
	float acc;
	float colorT;
	int state;
	
	virtual void init();
	virtual void reset();
	virtual void update(float elapsed);
	void update0(float elapsed);
	void update1(float elapsed);
	void update2(float elapsed);
};

#endif
