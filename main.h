// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// Setup file for main. Sets up variables, some types, etc. 
// Also includes all other headers as part of setup
#ifndef MAIN_H
#define MAIN_H

// include all other headers
#include <Adafruit_CircuitPlayground.h>
#include "color_defs.h"
#include "movement_defs.h"
#include "functions.h"

// system state vars
typedef enum {RESET_EXERCISE, READY, CHANGE_REPETITIONS, MEASURING, EXCERCISE_IN_PROGRESS, EXCERCISE_COMPLETE, ROUTINE_COMPLETE, ERROR} sys_state;

extern sys_state sysState; // system state 

// timeout vars
typedef enum {LEFT=1, RIGHT} debonce_input;

#define two_sec_timeout 2000 // timeout in millis
#define four_sec_timeout 4000 // timeout in millis
#define debounce_time 500 // debounce time in millis
#define sample_time 10 // sample time in millis

extern debonce_input debounceObj;
extern long timeout_start;
extern long timeout_curr;


// display vars for excercise percentage and repetition select
extern neopixel_color displayColor; 	// current display color 
extern uint8_t numDisplayed;	// number of pixels on

// vars for acceleration/movement tracking
//extern acceleration_axes currAccel;

typedef struct {
	accel_characteristic rise;
	accel_characteristic fall;
	neopixel_color color;
} exercise;

#define PUSH_UP ((exercise) {PUSH_UP_RISE, PUSH_UP_FALL, PUSH_UP_COLOR})
#define SIT_UP ((exercise) { SIT_UP_RISE, SIT_UP_FALL, SIT_UP_COLOR})
#define JUMPING_JACK ((exercise) {JUMPING_JACK_RISE, JUMPING_JACK_FALL, JUMPING_JACK_COLOR})
#define SQUAT ((exercise) {SQUAT_RISE, SQUAT_FALL, SQUAT_COLOR})

extern exercise currExercise;

#define sample_size 10
 extern accel_characteristic sampleArr[sample_size]; // maybe 20??? maybe 5???
// extern acceleration_axes sampleArr[sample_size];
extern uint8_t sampleCount;


// vars for excercise tracking
extern uint8_t repetitionNum;	// the number of repetitions in each exercise
extern uint8_t repetitionCompleted; // number of repetitions for currExercise

extern exercise excerciseArr[4]; // colors of completed exercises
extern uint8_t exerciseNum; // number of completed exercises

#endif

#ifndef NULL
#define NULL 0 
#endif
