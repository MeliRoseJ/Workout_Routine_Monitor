// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// color setup
#ifndef COLORS_H
#define COLORS_H

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
#define BLUE ((neopixel_color) {0. 0, 255})
#define PURPLE ((neopixel_color) {125, 0, 255})
#define PINK ((neopixel_color) {255, 0, 125})
#define WHITE ((neopixel_color) {255, 255, 255})

// Status LED color definitions
#define READY_COLOR ((neopixel_color) GREEN)
#define ERROR_COLOR ((neopixel_color) RED)
#define MEASURING_COLOR ((neopixel_color) BLUE)
#define COMPLETE_COLOR ((neopixel_color) WHITE)

// Exercise color definitions
#define SIT_UP_COLOR ((neopixel_color) ORANGE)
#define PUSH_UP_COLOR ((neopixel_color) PURPLE)
#define JUMPING_JACK_COLOR ((neopixel_color) CYAN)
#define SQUAT_COLOR ((neopixel_color) PINK)

// Repetition count level color definitions
#define ONES ORANGE
#define TENS YELLOW
#define TWENTIES CYAN
#define THRITIES PURPLE

#endif