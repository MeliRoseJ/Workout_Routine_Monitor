// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// movement setup
#ifndef MOVEMENT_DEFS_H
#define MOVEMENT_DEFS_H


// movement related types
typedef enum {INCREASE, DECREASE, CONSTANT} acceleration_change;

typedef struct {
	acceleration_change xChar;
	acceleration_change yChar;
	acceleration_change zChar;
} accel_characteristic;

typedef struct {
	float x;
	float y;
	float z;
} acceleration_axes;

typedef enum {NONE, POS, NEG} accel_sign
typedef struct {
	accel_sign xChar;
	accel_sign yChar;
	accel_sign zChar;
} accel_sign_char;


// #define SIT_UP_RISE ((accel_characteristic) {INCREASE, DECREASE, INCREASE}) 
// #define SIT_UP_FALL ((accel_characteristic) {DECREASE, INCREASE, DECREASE})
// #define SIT_UP_RISE_SIGN ((accel_sign_char) {NONE, NEG, NONE})
// #define SIT_UP_FALL_SIGN ((accel_sign_char) {NONE, POS, NONE})

// #define PUSH_UP_RISE ((accel_characteristic) {INCREASING, DECREASING, INCREASING}) 
// #define JUMPING_JACK_RISE ((accel_characteristic) {DECREASING, INCREASING, INCREASING})
// #define SQUAT_RISE ((accel_characteristic) {CONSTANT, INCREASING, CONSTANT})

// #define PUSH_UP_FALL ((accel_characteristic) {DECREASING, INCREASING, DECREASING})
// #define JUMPING_JACK_FALL ((accel_characteristic) {INCREASING, DECREASING, DECREASING})
// #define SQUAT_FALL ((accel_characteristic) {CONSTANT, DECREASING, CONSTANT})


#endif