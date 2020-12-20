// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// Neopixel/display file

#include <Adafruit_CircuitPlayground.h>
#include "setup.h"

void updateDisplay(sysState status, struct excercise excercises[]){
	CircuitPlayground.clearPixels();
	switch (status){
		case READY {
			// set status LED
			CircuitPlayground.setPixelColor(STATUS_LED, R_GREEN, G_GREEN, B_GREEN);
			// set excercise LEDs, if any
			int i;
			for (i = 0; i < sizeof(excercises); i++){
				CircuitPlayground.setPixelColor(i+1, excercises[i].redVal, excercises[i].greenVal, excercises[i].blueVal);
			}
		break;
	}
	case ERROR {
		// set status LED
		CircuitPlayground.setPixelColor(STATUS_LED, R_RED, G_RED, B_RED);

		// do not show completed excercises
		break;
	}
	default:
		int completion = getCompletion();