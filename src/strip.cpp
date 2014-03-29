#include "strip.h"
#include "activity.h"

//
Strip::Strip()
{
	for (int i = 0; i < MAX_ACTIVITIES; i++)
		activities[i] = 0;
	
	currentActivity = 0;
}

//no safety for exceeding MAX_ACTIVITIES
void Strip::addActivity(Activity *a)
{
	a->init();
	a->strip = this;
	
	int i = -1;
	while (activities[++i] != 0);
	
	activities[i] = a;
}

//
Activity *Strip::getActivity()
{
	return activities[currentActivity];
}

//
void Strip::onActivityFinish()
{
	//set to next activity
	currentActivity++;
	if (activities[currentActivity] == 0)
		currentActivity = 0;
}
