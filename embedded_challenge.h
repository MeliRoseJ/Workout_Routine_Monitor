// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// types setup
#ifndef TYPES_H
#define TYPES_H

/////////////////////////////////// STATE ///////////////////////////////////

// system state
typedef enum {RESET_EXERCISE, READY, CHANGE_REPETITIONS, MEASURING, EXERCISE_IN_PROGRESS, EXERCISE_COMPLETE, ROUTINE_COMPLETE} sys_state;


/////////////////////////////////// TIMING ///////////////////////////////////

#define two_sec_timeout 2000 // timeout in millis
#define four_sec_timeout 4000 // timeout in millis
#define debounce_time 200 // debounce time in millis

#define sample_time 20 // sample time in millis
#define measuring_sample_size 2
#define in_progress_sample_size 3

// debounce item
typedef enum {NONE, LEFT, RIGHT} debounce_input;

debounce_input debouncing;
long startTime;
long currTime;


/////////////////////////////////// COLORS ///////////////////////////////////

// Neopixel colors go from 0 to 255.

typedef struct { // RGB color information for a neopixel
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} neopixel_color;

// LED off
#define OFF_COLOR ((neopixel_color) {0,0,0})

// color definitions
#define RED ((neopixel_color) {255, 0, 0})
#define ORANGE ((neopixel_color) {255, 125, 0})
#define YELLOW ((neopixel_color) {255, 255 , 0})
#define GREEN ((neopixel_color) {0, 255 , 0})
#define CYAN ((neopixel_color) {0, 255, 255})
#define BLUE ((neopixel_color) {0, 0, 255})
#define PURPLE ((neopixel_color) {100, 0, 255})
#define PINK ((neopixel_color) {255, 0, 100})
#define WHITE ((neopixel_color) {255, 255, 255})

// Status LED color definitions
#define RESET_COLOR ((neopixel_color) YELLOW)
#define READY_COLOR ((neopixel_color) GREEN)
#define MEASURING_COLOR ((neopixel_color) BLUE)
#define COMPLETE_COLOR ((neopixel_color) WHITE)

// Exercise color definitions
#define SIT_UP_COLOR ((neopixel_color) ORANGE)
#define PUSH_UP_COLOR ((neopixel_color) RED)
#define JUMPING_JACK_COLOR ((neopixel_color) CYAN)
#define SQUAT_COLOR ((neopixel_color) PINK)

// Repetition count level color definitions
#define ONES_COLOR ORANGE
#define TENS_COLOR YELLOW
#define TWENTIES_COLOR CYAN
#define THIRTIES_COLOR PURPLE

// display vars for exercise percentage and repetition select
neopixel_color displayColor; 	// current display color 
int displayNum;	// number of pixels on

////////////////////////////// ACCELERATION //////////////////////////////

// acceleration struct
typedef struct {
	int x;
	int y;
	int z;
} accel_axes;

#define NULL_ACCEL_AXES ((accel_axes) {0,0,0})

#define SIT_UP_THRESHOLD ((accel_axes) {8, -1, 5})
// #define SIT_UP_UP_THRESHOLD ((accel_axes) {3, 6, 5}) 
// #define SIT_UP_ACCEL_TOP  ((accel_axes) {0, -4, 9})
// #define SIT_UP_ACCEL_BOTTOM ((accel_axes) {0, 6,7})

// #define PUSH_UP_UP_THRESHOLD ((accel_axes) {-7, -3, 0})
#define PUSH_UP_THRESHOLD ((accel_axes) {-6, -3, -1})
// #define PUSH_UP_ACCEL_TOP ((accel_axes) {-4,-8,-2})
// #define PUSH_UP_ACCEL_BOTTOM ((accel_axes) {-8,0,0})

// #define SQUAT_UP_THRESHOLD ((accel_axes) {2, -7, 5})
#define SQUAT_THRESHOLD ((accel_axes) {-1, -6, 6})
// #define SQUAT_ACCEL_TOP ((accel_axes) {0,-5,6})
// #define SQUAT_ACCEL_BOTTOM ((accel_axes) {0,-5,6})

#define JUMPING_JACK_THRESHOLD ((accel_axes) {-5, -11, 6})
// #define JUMPING_JACK_DOWN_THRESHOLD ((accel_axes) {-4, -10, 5})
// #define JUMPING_JACK_ACCEL_TOP ((accel_axes) {-2, 4, 8})
// #define JUMPING_JACK_ACCEL_BOTTOM ((accel_axes) {0, -9, 1})


// acceleration variables
accel_axes currAccel;
accel_axes prevAccel;

////////////////////////////// EXERCISE //////////////////////////////

typedef struct {
	accel_axes threshold;
	// accel_axes downThreshold;
	neopixel_color color;
} exercise;


#define NULL_EXERCISE ((exercise) {{0,0,0}, OFF_COLOR})

#define SIT_UP ((exercise) {SIT_UP_THRESHOLD, SIT_UP_COLOR})
#define PUSH_UP ((exercise) {PUSH_UP_THRESHOLD, PUSH_UP_COLOR})
#define SQUAT ((exercise) {SQUAT_THRESHOLD, SQUAT_COLOR})
#define JUMPING_JACK ((exercise) {JUMPING_JACK_THRESHOLD, JUMPING_JACK_COLOR})

exercise measuredExercise;
int sampleCount;

exercise exerciseArr[4]; // colors of completed exercises
int currExercise; // number of completed exercises


#endif