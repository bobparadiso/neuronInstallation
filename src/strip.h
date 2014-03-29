#ifndef _strip_h_
#define _strip_h_

class Activity;

#define MAX_ACTIVITIES 10

class Strip
{
public:
	Activity *activities[MAX_ACTIVITIES];
	int currentActivity;
	int length;
	int index;
	int pixels; //pixel offset
	
	Strip();
	void addActivity(Activity *a);
	Activity *getActivity();
	void onActivityFinish();
};

#endif
