#ifndef _activity3_h_
#define _activity3_h_

#include "activity.h"

class Activity3 : public Activity
{
public:
	float pos;
	int size;
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
