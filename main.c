// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// main file

#include <Adafruit_CircuitPlayground.h>
#include "setup.h"

/*
 * Note that the circuit playground library comes with functions to support 
 * its built-in input and output devices, so this code will not be worrying 
 * about those pins when setting up things like DDRs. 

 * However, if these pins need to be used for interrupts, their pin mapping
 * will be used according to the Adafruit_Circuit_Playground.h file from the 
 * repository: https://github.com/adafruit/Adafruit_CircuitPlayground
 */

/* 
8MHz clk with 1024 prescaler (all ticks rounded up):
	- 1 ms = 1000 hz = 7 ticks
	- 10 ms = 100 hz = 78 ticks
	- 100 ms = 10 hz = 781 ticks
	- 1 s = 1 hz = 7812 ticks
	- 2 s = 1/3 (repeat) hz = 23437 ticks
	- 4 s = 0.25 hz = 31249 ticks
	- 5 s = 0.2 hz = 39062 ticks
	- 6 s = 1/6 hz = 46874 ticks
	- 7 s = 1/7 hz = 54687 ticks
	- 8 s = 0.125 hz = 62499 ticks
	- 9 s = 1/9 hz = 70312 ticks (out of timer range)
	MAX: 65535 ticks, or about 8.4 seconds (65624)
*/

// other (global) variables found in setup.h
uint8_t i, j, k; // loop variables

void setup() {
	// Instead of setting up individual timers, millis will be used to 
	// determine if a certain time has passed

	CircuitPlayground.setBrightness(100);
	
	repetitionNum = 10; // default exercise length
	for (i = 0; i < sizeof(exerciseArr); i++)
		exerciseArr[i] = NULL; // OFF_COLOR; ****** fix
			
	sysState = RESET_EXERCISE;

}

void loop() {
	switch(sysState){
		case RESET_EXERCISE:
			debounceObj = NULL;
			timeout_start = 0;
			timeout_curr = 0;

			currColor = OFF_COLOR;
			numDisplayed = 0;
			
			lastCharacteristic = NULL; //{NULL, NULL, NULL};
			currCharacteristic = NULL; //{NULL, NULL, NULL};
			matchCharacteristic = 0;
			
			repetitionCompleted = 0;
			exerciseArr[exerciseNum] = NULL;
			
			sysState = READY;
			break;

		case READY:
			updateDisplay_statusLEDs(READY_COLOR);

			timeout_curr = millis() - timeout_start;

			// right button pressed and left button not being debounced
			if (i = debounceRight()){
				if (i == 2)
					sysState = CHANGE_REPETITIONS;
			}
			// left button pressed and right button not being debounced
			else if (i = debounceLeft()){
				if (i == 2)
					sysState = MEASURING;
			}
			// if no buttons pressed at end of debounce time, debounce failed
			else if (timeout_start >= debounce_time) { 
				debounceObj = NULL;
				timeout_start = 0;
			}
			break;

		case CHANGE_REPETITIONS:
			// determine display values
			if(!(displayNum = repetitionNum % 10))
				displayNum = 10;

			if (repetitionNum <= 10) 
				displayColor = ONES_COLOR;
			else if (repetitionNum <= 20)
				displayColor = TENS_COLOR;
			else if (repetitionNum <= 30)
				displayColor = TWENTIES_COLOR;
			else displayColor = THIRTIES_COLOR; 

			updateDisplay_oneColor(displayColor, displayNum);
			timeout_curr = millis() - timeout_start;

			if (i = debounceLeft()) {
				if (i == 2 &&(repetitionNum > 0))
					repetitionNum++;
			}
			else if (i = debounceRight()) {
				if (i == 2 && (repetitionNum < 41))
					repetitionNum--;
			}
			else if (debounceObj && (timeout_curr >= debounce_time)) {
				debounceObj = NULL;
				timeout_start = 0;
			}
			// if no debounce is happening & no buttons pressed for 4 seconds
			else if (!debounceObj && (timeout_curr >= four_sec_timeout)) {
				timeout_start = 0;
				sysState = READY;
			}
			break;

		case MEASURING:
			updateDisplay_statusLEDs(MEASURING_COLOR);

			// *********** note be careful ab timeout start being zero. 
			// *********** millis() - 0 is probably bigger than debounce_time
			timeout_curr = millis() - timeout_start;
			if (i == debounceLeft()){
				if (i == 2) {
					sysState = READY;
				}
			}
			else if (debounceObj && (timeout_curr >= debounce_time)){
				debounceObj = NULL;
				timeout_start = 0;
			}
			else { // measure movement
				if (timeout_curr >= sample_time){
					sampleArr[sampleCount] = getAcceleration(); // getCharacteristic
					sampleCount++;
					timeout_start = 0;
				}
				else if (sampleCount == sample_size){ // if or else if??
					if(currExercise = getExercise()) {
						// add condition if excercise has already been done
						exerciseArr[exerciseNum] = currExercise;
						// repetitionCompleted
						// exerciseNum++; // don't increment until complete
						sysState = EXERCISE_IN_PROGRESS;
					}
					else sampleCount = 0; // restart if unidentifiable
				}
			}
			break;

		case EXERCISE_IN_PROGRESS:
			displayColor = currExercise.color;
			displayNum = (repetitionCompleted/repetitionNum)*10;
			updateDisplay_oneColor(displayColor, displayNum);
			
			// *********** note be careful ab timeout start being zero. 
			// *********** millis() - 0 is probably bigger than debounce_time
			timeout_curr = millis() - timeout_start;
			if (i == debounceLeft()){
				if (i == 2) {
					sysState = READY;
				}
			}
			else if (debounceObj && (timeout_curr >= debounce_time)){
				debounceObj = NULL;
				timeout_start = 0;
			}
			else { // count movements
				/////////////////////////////////////////////////
				if (repetitionCompleted == repetitionNum){
					exerciseNum++;
					sysState = EXERCISE_COMPLETE;
				}
			}
			break;

		case EXERCISE_COMPLETE:
			updateDisplay_oneColor(COMPLETE_COLOR, 10);
			timeout_curr = millis() - timeout_start;

			if (timeout_curr >= four_sec_timeout)
				sysState = READY;

			break;

		case ROUTINE_COMPLETE:
			updateDisplay_statusLEDs(COMPLETE_COLOR);
			// sysState = ROUTINE_COMPLETE;
			break;
		
		case ERROR:
			updateDisplay_statusLEDs(ERROR_COLOR);

			timeout_curr = millis() - timeout_start;

			if (timeout_curr >= four_sec_timeout)
				sysState = RESET_EXERCISE;
			break;
	}
}



