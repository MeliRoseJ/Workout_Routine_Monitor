// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// function header

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "embedded_challenge.h"

// display the status LEDs
void updateDisplay_statusLEDs(neopixel_color statusColor);

// display a single color with varying number of LEDs on
void updateDisplay_oneColor();

// get current time. return millis() - start if start is not 0, else return 0
void setCurrTime();

// return 0 if can't debounce or not pressed, return 1 if in process, return 2 if complete
int checkLeftDebounce();
int checkRightDebounce();

void getAcceleration();
// void getCharacteristic();

void getExercise();
// void updatePercentChar();
accel_axes getAccelAvg();
int meetsThreshold(accel_axes avg, accel_axes thresh);

// operators
// int operator==(accel_characteristic a, accel_characteristic b);
// int operator!=(accel_characteristic a, accel_characteristic b);

// int operator==(percent_characteristic a, percent_characteristic b);
// int operator!=(percent_characteristic a, percent_characteristic b);
// int operator<=(percent_characteristic a, percent_characteristic b);
// int operator>=(percent_characteristic a, percent_characteristic b);

int operator==(accel_axes a, accel_axes b);
int operator!=(accel_axes a, accel_axes b);
int operator<=(accel_axes a, accel_axes b);
int operator>=(accel_axes a, accel_axes b);

int operator==(exercise a, exercise b);
int operator!=(exercise a, exercise b);

int operator==(neopixel_color a, neopixel_color b);
int operator!=(neopixel_color a, neopixel_color b);
#endif
