//Trail, bright in center

#include <string.h>
#include <inttypes.h>

#include "activityDebug.h"
#include "config.h"
#include "strip.h"
#include "util.h"

//
void activityDebug(strip_t *s, float elapsed)
{
	int i;
	uint8_t c = 170;
	for (i = 0; i < s->length; i++)
	{
		setPixel(s->pixels + i, c, c, c);
	}
}
