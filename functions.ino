// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// function definitions

#include <Adafruit_CircuitPlayground.h>
#include "functions.h"

#include "embedded_challenge.h"


// display the status LEDs
void updateDisplay_statusLEDs(neopixel_color statusColor) {
	int i;

	// Status LED
	CircuitPlayground.setPixelColor(0, statusColor.red, statusColor.green, statusColor.blue);

	// Exercise LED
	for (i = 1; i < 5; i++) { 
		neopixel_color color = exerciseArr[i-1].color; 
		CircuitPlayground.setPixelColor(i, color.red, color.green, color.blue);
	}
	// Remaining LEDs - turn off
	for (i = 5; i < 11; i++) 
		CircuitPlayground.setPixelColor(i, 0, 0, 0);
}

// display a single color with varying number of LEDs on
void updateDisplay_oneColor(){
	int i;
	// LEDs with on values
	for (i = 0; i < displayNum; i++)
		CircuitPlayground.setPixelColor(i, displayColor.red, displayColor.green, displayColor.blue);
	// Remaining LEDs - turn off
	for (i = displayNum; i < 11; i++)
		CircuitPlayground.setPixelColor(i, 0, 0, 0);
}

void setCurrTime(){
	if (startTime) // start time not 0
		currTime = millis() - startTime;
	else currTime = 0;
}

int checkLeftDebounce(){
	if (CircuitPlayground.leftButton() && (debouncing != RIGHT)) {
		if (debouncing == NONE) { // begin debouncing left button
			startTime = millis();
			debouncing =  LEFT;	
		} else if (debouncing && (currTime >= debounce_time)){ // debounce complete
			startTime = 0;
			debouncing= NONE;
			return 2;
		}
		return 1;
	}
	return 0;
}

int checkRightDebounce(){
	if (CircuitPlayground.rightButton() && (debouncing != LEFT)) {
		if (debouncing == NONE) { // begin debouncing left button
			startTime = millis();
			debouncing =  RIGHT;	
		} else if (debouncing && (currTime >= debounce_time)){ // debounce complete
			startTime = 0;
			debouncing = NONE;
			return 2;
		}
		return 1;
	}
		// Serial.println("D");

	return 0;
}

void getAcceleration(){
	currAccel = ((accel_axes) {CircuitPlayground.motionX(), CircuitPlayground.motionY(), CircuitPlayground.motionZ()});
	// Serial.print(currAccel.x);
	// Serial.print(", ");
	// Serial.print(currAccel.y);
	// Serial.print(", ");
	// Serial.println(currAccel.z);
}

accel_axes getAccelAvg(){
	accel_axes res;
	res.x = (currAccel.x + prevAccel.x)/2;
	res.y = (currAccel.y + prevAccel.y)/2;
	res.z = (currAccel.z + prevAccel.z)/2;
	return res;
}

void getExercise(){
	// accel_axes average = getAccelAvg();
	// Serial.print("average: ");
	// Serial.print(average.x);
	// Serial.print(",");
	// Serial.print(average.y);
	// Serial.print(",");
	// Serial.println(average.z);
	//Serial.print("average: ");
	Serial.print(currAccel.x);
	Serial.print(",");
	Serial.print(currAccel.y);
	Serial.print(",");
	Serial.println(currAccel.z);
	exercise res;
	// if (average == NULL_ACCEL_AXES)
	// 	res = NULL_EXERCISE;
	// if (meetsThreshold(average, JUMPING_JACK_UP_THRESHOLD))
	// 	res = JUMPING_JACK;
	// else if (meetsThreshold(average, PUSH_UP_UP_THRESHOLD))
	// 	res = PUSH_UP;
	// else if (meetsThreshold(average, SQUAT_UP_THRESHOLD))
	// 	res = SQUAT;
	// else if (meetsThreshold(average, SIT_UP_UP_THRESHOLD))
	// 	res = SIT_UP;
	if (meetsThreshold(currAccel, JUMPING_JACK_THRESHOLD))
		res = JUMPING_JACK;
	else if (meetsThreshold(currAccel, PUSH_UP_THRESHOLD))
		res = PUSH_UP;
	else if (meetsThreshold(currAccel, SQUAT_THRESHOLD))
		res = SQUAT;
	else if (meetsThreshold(currAccel, SIT_UP_THRESHOLD))
		res = SIT_UP;
	else
		res = NULL_EXERCISE;

	// if (res != NULL_EXERCISE){
	// 	if (measuredExercise != NULL_EXERCISE)
	// 		sampleCount++;
	// if (sampleCount == measuring_sample_size)
	// if (measuredExercise != NULL_EXERCISE){
	// 	if (res == measuredExercise)
	// 		sampleCount++;
	// 	else if (sampleCount > 0)
	// 		sampleCount--;
	// 	else {
	// 		measuredExercise = NULL_EXERCISE;
	// 		sampleCount = 0;
	// 	}
	// }
	// else {// if (measuredExercise == NULL_EXERCISE){
	// 	measuredExercise = res;
	// 	sampleCount = 1;
	// }


	if (measuredExercise != NULL_EXERCISE && res == measuredExercise)
		sampleCount++;
	else if (res != NULL_EXERCISE) {
		measuredExercise = res;
		sampleCount = 1;
	}
	else {
		measuredExercise = NULL_EXERCISE;
		sampleCount = 0;
	}
}



int meetsThreshold(accel_axes a, accel_axes thresh){
	if (thresh.x > 0 && a.x < thresh.x)
		return 0;
	else if (thresh.x < 0 && a.x > thresh.x)
		return 0;
	if  (thresh.y > 0 && a.y < thresh.y)
		return 0;
	else if (thresh.y < 0 && a.y > thresh.y)
		return 0;
	if  (thresh.z > 0 && a.z < thresh.z)
		return 0;
	else if (thresh.z < 0 && a.z > thresh.z)
		return 0;
	return 1;
}


int operator==(accel_axes a, accel_axes b){
  if (a.x != b.x)
    return 0;
  if (a.y != b.y)
    return 0;
  if (a.z != b.z)
    return 0;
  return 1;
}
int operator!=(accel_axes a, accel_axes b){
  return !(a == b);
}
int operator<=(accel_axes a, accel_axes b){
	if (a.x > b.x)
		return 0;
	if (a.y > b.y)
		return 0;
	if (a.z > b.z)
		return 0;
	return 1;
}
int operator>=(accel_axes a, accel_axes b){
	if (a.x < b.x)
		return 0;
	if (a.y < b.y)
		return 0;
	if (a.z < b.z)
		return 0;
	return 1;
}

int operator==(exercise a, exercise b){
  if (a.threshold != b.threshold)
    return 0;
  // if (a.downThreshold != b.downThreshold)
  //   return 0;
  // if (a.constCount != b.constCount)
  // 	return 0;
  if (a.color != b.color)
    return 0;
  return 1;
}
int operator!=(exercise a, exercise b){
  return !(a == b);
}

int operator==(neopixel_color a, neopixel_color b){
  if (a.red != b.red)
    return 0;
  if (a.green != b.green)
    return 0;
  if (a.blue != b.blue)
    return 0;
  return 1;
}
int operator!=(neopixel_color a, neopixel_color b){
  return !(a == b);
}
