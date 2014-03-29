#ifndef _activity1_h_
#define _activity1_h_

#include "activity.h"

class Activity1 : public Activity
{
public:
	float pos;
	const int *sizes;
	const int *speeds;
	int size;
	float speed;
	int dir;
	float coolDown;
	float clock;
	int state;

	virtual void init();
	virtual void reset();
	virtual void update(float elapsed);
	void randomize();
	void update0(float elapsed);
	void update1(float elapsed);
};

#endif
