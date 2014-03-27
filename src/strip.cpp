#include "strip.h"
#include "activity.h"

//
void setActivity(Strip *s, Activity *a)
{
	a->init();
	
	s->activity = a;
	a->strip = s;
}
