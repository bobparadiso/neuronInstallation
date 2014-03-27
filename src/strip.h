#ifndef _strip_h_
#define _strip_h_

class Activity;

class Strip
{
public:
	Activity *activity;
	int length;
	int index;
	int pixels; //pixel offset
};

void setActivity(Strip *s, Activity *a);

#endif
