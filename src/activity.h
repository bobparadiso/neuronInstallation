#ifndef _activity_h_
#define _activity_h_

#include "strip.h"

class Activity
{
public:
	Strip *strip;

	virtual void init() {reset();};
	virtual void reset() {};
	virtual void update(float elapsed);
};

#endif
