#ifndef _strip_h_
#define _strip_h_

typedef struct strip
{
	void (*update)(struct strip *s, float elapsed);
	int length;
	int index;
	int pixels; //pixel offset
	void *data;
} strip_t;

#endif
