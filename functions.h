// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// function header

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// display the status LEDs
//void updateDisplay_statusLEDs(neopixel_color statusColor, neopixel_color exerciseColors[4]);
void updateDisplay_statusLEDs(neopixel_color statusColor);
// display a single color with varying number of LEDs on
void updateDisplay_oneColor(neopixel_color color, uint8_t numLEDs);
// void updateDisplay_oneColor();

// begins the debounce process if necessary. returns 1 if button is in the process of debouncing or has finished debouncing. Returns 0 if it is not the button currently being debounced, or if it is unpressed (the debounce process cannot be begun)
// bool debounceLeft(sys_state stateIfDebounced);
// bool debounceRight(sys_state stateIfDebounced);
// return 0 if can't debounce or not pressed, return 1 if in process, return 2 if complete
uint8_t debounceLeft();
uint8_t debounceRight();

acceleration_axes getAcceleration();
accel_characteristic getCharacteristic();
exercise getExercise();
#endif