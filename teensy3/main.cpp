/*
    neuronInstallation program

    uses:
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html

  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.
*/

#include "WProgram.h"

#include <OctoWS2811.h>

#include "config.h"

#include "activity1.h"
#include "activity2.h"
#include "activity3.h"
#include "activity5.h"
#include "activityDebug.h"

#define BUF_SIZE (LONGEST_STRIP*24)

DMAMEM char displayMemory[BUF_SIZE];
char drawingMemory[BUF_SIZE];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(LONGEST_STRIP, displayMemory, drawingMemory, config);

#define STATUS_LED 13

extern "C" int main(void)
{
	leds.begin();
	
	//strips
	strip_t strips[NUM_STRIPS];
	for (int i = 0; i < NUM_STRIPS; i++)
	{
		strips[i] = (strip_t){
			.update = NULL,
			.length = 0,
			.index = i,
			.pixels = i * LONGEST_STRIP,
			.data = NULL
		};
	}

	//set activities

	setupActivity2(&strips[0], (activity2_t){
		.pos = 0.0f,
		.size = 30,
		.dir = 1,
		.speed = 50.0f
	});

	setupActivity3(&strips[1], (activity3_t){
		.pos = 0.0f,
		.size = 10,
		.speed = 30.0f,
		.coolDown = 15.0f,
		.clock = 0.0f,
		.state = 0
	});

	setupActivity1(&strips[2], (activity1_t){
		.pos = 0.0f,
		.size = 10,
		.dir = 1,
		.speed = 50.0f
	});

	setupActivity1(&strips[3], (activity1_t){
		.pos = 0.0f,
		.size = 25,
		.dir = 1,
		.speed = 50.0f
	});

	setupActivity1(&strips[4], (activity1_t){
		.pos = 0.0f,
		.size = 10,
		.dir = 1,
		.speed = 50.0f
	});

	setupActivity5(&strips[5], (activity5_t){
		.pos = 0.0f,
		.size = 10,
		.dir = 1,
		.speed = 140.0f,
		.c1 = {1.0f, 1.0f, 1.0f},
		.c2 = {1.0f, 0.0f, 0.0f},
		.c3 = {1.0f, 0.9f, 0.0f},
		.colorT = 0.0f,
		.colorPos1 = 225,
		.colorVel2 = 1.0f,
		.state = 0
	});
	
	setupActivity5(&strips[6], (activity5_t){
		.pos = 0.0f,
		.size = 10,
		.dir = 1,
		.speed = 10.0f,
		.c1 = {1.0f, 1.0f, 1.0f},
		.c2 = {0.0f, 0.0f, 1.0f},
		.c3 = {0.0f, 0.9f, 1.0f},
		.colorT = 0.0f,
		.colorPos1 = 160,
		.colorVel2 = 1.0f,
		.state = 0
	});

	setupActivity2(&strips[7], (activity2_t){
		.pos = 0.0f,
		.size = 20,
		.dir = 1,
		.speed = 50.0f
	});

	//strip lengths
	strips[0].length = 448;
	strips[1].length = 240;
	strips[2].length = 643;
	strips[3].length = 421;
	strips[4].length = 348;
  	strips[5].length = 330;
  	strips[6].length = 240;
	strips[7].length = 448;

	pinMode(STATUS_LED, OUTPUT);
	bool stat = true;	

	long lastTime = micros();
	while (true)
	{
		digitalWriteFast(STATUS_LED, stat ? HIGH : LOW);
		stat = !stat;

		//calc elapsed time
		long time = micros();
		if (time < lastTime)
			lastTime = time;//easy deal with wrap around
		float elapsed = (time - lastTime) * 0.000001f;
		lastTime = time;

		//clear buffer
		memset(drawingMemory, 0, BUF_SIZE);

		for (int t = 0; t < NUM_STRIPS; t++)
			if (strips[t].update)
				strips[t].update(&strips[t], elapsed);

		leds.show();
	}
}

