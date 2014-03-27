#ifndef _activity2_h_
#define _activity2_h_

#include "activity.h"

class Activity2 : public Activity
{
public:
	float pos;
	int size;
	int dir;
	float speed;
	float coolDown;
	float clock;
	int state;
	
	virtual void reset();
	virtual void update(float elapsed);
	void update0(float elapsed);
	void update1(float elapsed);
};

#endif
