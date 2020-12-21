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
int i, j, k; // loop variables

void setup() {
	// Instead of setting up individual timers, millis will be used to 
	// determine if a certain time has passed

	// ATmega32U4 default clock source is 1MHz system clock with 8MHz crystal
	// With CTC, OCRnx = f_clk_IO / (prescaler * desired frequency) - 1, 
	// so there is a compare match at that value

	// Timer1 will be used to refresh the display every 1/10th second (10 Hz), 
	// so the minimum prescaler needed is 64. OCR1A used as TOP so = 12499 
	TCCR1A = 0b00000000; // All ports disconnected, WGM in CTC (0b01[00])
	TCCR1B = 0b00001011; // WGM in CTC (0b[01]00), prescaler to 64
	// TCCR1C = 0b00000000; // Don't force output compare 

	OCR1AH = (12499 >> 8); // upper 8 bits
	OCR1AL = (12499 & 0xFF); // lower 8 bits

	TIMSK1 = 0b00000010; // the display interrupt will always run if interrupts are enabled
	// Later, to enable interrupts on OCR1A match, TIMSK1 |= (1 << 1)

	// Timer2 will be used to sample the accelerometer. The sample rate will be
	// 100Hz (10ms), so the minimum prescaler needed is 8. So OCR2A = 9999
	TCCR2A = 0b00000000; // All ports disconnected, WGM in CTC (0b01[00])
	TCCR2B = 0b00001010; // WGM in CTC (0b[01]00), prescaler to 8
	// TCCR2C = 0b00000000; // Don't force output compare 

	OCR2AH = (9999 >> 8); // upper 8 bits of 9999
	OCR2AL = (9999 & 0xFF); // lower 8 bits of 9999

	// Timer interrupts will be enabled in RESET state
	//TIMSK2 = 0b00000000; // for now interrupts turned off.
	// Later, to enable interrupts on OCR2A match, TIMSK2 |= (1 << 1)

	// // Timer3 will be as a timeout for if the user is idle during certain 
	// // states. These timeouts will be several seconds long, so the best 
	// // prescaler is 1024. The timer will be reset with each new state that 
	// // uses it, and each state will use a different OCR interrupt.

	// // OCR3A will be 2 sec, OCR3B will be 4 sec, and OCR3C will be 6 sec
	// // The MAX or TOP will be about 8.4 sec (a bit short of that)
	// TCCR3A = 0b00000000; // All ports disconnected, WGM in Normal (0b00[00])
	// TCCR3B = 0b00000101; // WGM in normal (0b[00]00), prescaler to 1024
	// // TCCR3C = 0b00000000; // Don't force output compare

	// OCR3AH = (23437 >> 8); // upper 8 bits
	// OCR3AL = (23437 & 0xFF); // lower 8 bits
	// OCR3BH = (31249 >> 8); // upper 8 bits
	// OCR3BL = (31249 & 0xFF); // lower 8 bits
	// OCR3CH = (46874 >> 8); // upper 8 bits
	// OCR3CL = (46874 & 0xFF); // lower 8 bits

	// // Timer interrupts will be enabled in RESET state
	// // TIMSK3 = 0b00000000; // for now interrupts turned off.
	// // Later, to enable interrupts on match:
	// // OVF -> TIMSK3 |= (1 << 0), OCR3A -> TIMSK3 |= (1 << 1), 
	// // OCR3B -> TIMSK3 |= (1 << 2), OCR3C -> TIMSK3 |= (1 << 3)

	// setBrightness(100);
	sysState = SETUP;
}

void loop() {
	switch(sysState){
		case RESET:
			cli(); // don't allow interrupts while resetting
			exerciseLength = 10; // default exercise length
			currColor = OFF_COLOR;
			numDisplayed = 0;
			
			exerciseNum = 0;
			for (i = 0; i < sizeof(exerciseArr); i++)
				exerciseArr[i] = OFF_COLOR;
			
			// for (i = 1; i < sizeof(currDisplay); i++)
			// 	currDisplay[i] = OFF_COLOR;
			
			TIMSK1 = 0b00000010; // turn on display interrupt
			TIMSK2 = 0b00000000; // for now interrupts turned off.
			// TIMSK3 = 0b00000000; // for now interrupts turned off.

			sysState = READY;
			sei(); // enable interrupts
			break;

		case READY:
			if (rightButton() && !exerciseNum) { 
				sysState = INPUT_LENGTH;
				timeout_start = millis();
				// TCNT3 = 0; // reset timer
				// TIMSK3 |= (1 << 2); // begin 4 sec timeout counter
			}
			else if (leftButton()) {
				sysState = MEASURING;
				timeout_start = millis();
				// TCNT3 = 0; // reset timer
				// TIMSK3 |= (1 << 2); // begin 4 sec timeout counter
			}
			
			break;

		case INPUT_LENGTH:
			// fix this somehow. logic is wrong i know it
			if ((millis() - timeout_start) >= four_sec_timeout)
				sysState = READY;
				break;
			
			else if (leftButton() && (exerciseLength > 0)) {
				exerciseLength--;
				if (!(exerciseLength%10))
					numDisplayed = 10;

				if (exerciseLength <= 10) 
					currColor = ONES;
				else if (exerciseLength <= 20)
					currColor = TENS;
				else if (exerciseLength <= 30)
					currColor = TWENTIES;
				else currColor = THIRTIES; 
			}
			else if (rightButton() && (exerciseLength < 41)) {
				exerciseLength++;
				numDisplayed = exerciseLength%10;
				if (exerciseLength <= 10) 
					currColor = ONES;
				else if (exerciseLength <= 20)
					currColor = TENS;
				else if (exerciseLength <= 30)
					currColor = TWENTIES;
				else currColor = THIRTIES; 
			}
			// else if (leftButton() || rightButton())
			// 	timeout_start = millis();
			break;

		case MEASURING:
			// should also set currColor = exercise color
			break;
		case IN_PROGRESS:
			if (leftButton()) {
				if ((millis() - timeout_start) >= two_sec_timeout){
					sysState = READY;
					break;
				}
			}
			else if (currMovement != prevMovement) {
			///////////////////////////////////
			break;
		case COMPLETE:
			break;
		case ERROR:
			break;
	}
}



