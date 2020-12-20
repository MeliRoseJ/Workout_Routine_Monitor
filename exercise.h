// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// exercise setup
#ifndef EXERCISE_H
#define EXERCISE_H

// exercise types
// typedef enum {NONE, SIT_UP, PUSH_UP, JUMPING_JACK, SQUAT} exercise_type;

// movement related types
typedef enum {INCREASING, DECREASING, CONSTANT} movement_characteristic;

typedef struct {
	movement_characteristic xChar;
	movement_characteristic yChar;
	movement_characteristic zChar;
} movement;

typedef struct {
	float x;
	float y;
	float z;
} acceleration;


// all definitions for UPWARD motion. (down -> up)
#define SIT_UP_RISE ((movement) {INCREASING, DECREASING, CONSTANT}) // gravity at down: z, up: y.
#define PUSH_UP_RISE ((movement) {INCREASING, DECREASING, INCREASING}) // Y maybe constant?
#define JUMPING_JACK_RISE ((movement) {DECREASING, INCREASING, INCREASING})
#define SQUAT_RISE ((movement) {CONSTANT, INCREASING, CONSTANT})

#define SIT_UP_FALL ((movement) {DECREASING, INCREASING, CONSTANT})
#define PUSH_UP_FALL ((movement) {DECREASING, INCREASING, DECREASING})
#define JUMPING_JACK_FALL ((movement) {INCREASING, DECREASING, DECREASING})
#define SQUAT_FALL ((movement) {CONSTANT, DECREASING, CONSTANT})


#endif