// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// Setup file for main. Sets up variables, some types, etc. 
// Also includes all other headers as part of setup
#ifndef SETUP_H
#define SETUP_H

// include all other headers
#include "neopixel_color.h"
#include "exercise.h"

// system states
typedef enum {RESET, READY, CHANGE_REPETITIONS, MEASURING, IN_PROGRESS, COMPLETE, ERROR} sys_state;

// status led indexes
enum status_LED_index {STATUS_LED, EX1_LED, EX2_LED, EX3_LED, EX4_LED};

#define two_sec_timeout 2000 // timeout in millis
#define four_sec_timeout 4000 // timeout in millis

extern volatile sys_state sysState; // system state 

extern uint8_t exerciseLength;	// the number of repetitions in each exercise
extern neopixel_color currColor; 	// current display color (for exercise 
									// percentage or repetition select) 
extern uint8_t numDisplayed;	// number of things displayed (for exercise 
								// percentage or repetition select) 

extern uint8_t exerciseNum; // number of completed exercises
extern uint8_t repetitionNum;
// extern exercise_type exerciseArr[4]; // completed exercises
extern neopixel_color excerciseArr[4]; // colors of completed exercises

extern long timeout_start;
extern long timeout_end;
// extern exercise_type currExercise;
// extern neopixel_color statusLEDs[5]; 	// Status LED will be 0, first 
										// exercise will be 1, etc
// extern neopixel_color currDisplay[10]; // the current display for neopixels

extern volatile acceleration lastAccel; 
extern volatile movement exerciseMovement;

#endif
