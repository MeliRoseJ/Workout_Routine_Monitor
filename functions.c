// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// function definitions

#include "main.h"

// display the status LEDs
void updateDisplay_statusLEDs(neopixel_color statusColor) { //, neopixel_color exerciseColors[4]){	
	uint8_t i = 0;

	// Status LED
	CircuitPlayground.setPixelColor(0, statusColor.red, statusColor.green, statusColor.blue);
	// Excercise LED
	for (i = 1; i < 5; i++) { 
		neopixel_color color = excerciseArr[i].color; 
		CircuitPlayground.setPixelColor(i, color.red, color.green, color.blue);
	}
	// Remaining LEDs - turn off
	for (i = 5; i < 11; i++) 
		CircuitPlayground.setPixelColor(i, 0, 0, 0);
}

display a single color with varying number of LEDs on
void updateDisplay_oneColor(neopixel_color color, uint8_t numLEDs){
	uint8_t i;
	// LEDs with on values
	for (i = 0; i < numLEDs; i++)
		CircuitPlayground.setPixelColor(i, color.red, color.green, color.blue);
	// Remaining LEDs - turn off
	for (i = numLEDs; i < 11; i++)
		CircuitPlayground.setPixelColor(i, 0, 0, 0);
}
// void updateDisplay_oneColor() { 
// 	uint8_t i;
// 	// LEDs with on values
// 	for (i = 0; i < displayNum; i++)
// 		CircuitPlayground.setPixelColor(i, displayColor.red, displayColor.green, displayColor.blue);
// 	// Remaining LEDs - turn off
// 	for (i = numLEDs; i < 11; i++)
// 		CircuitPlayground.setPixelColor(i, 0, 0, 0);
// }

uint8_t debounceLeft(){
	if (leftButton() && (debounceObj != RIGHT)) {
		if (!timeout_start) { // begin debouncing left button
			timeout_start = millis();
			debounceObj =  LEFT;	
		} else if (timeout_curr >= debounce_time){ // debounce complete
			timeout_start = 0;
			debounceObj = NULL;
			return 2;
		}
		return 1;
	}
	return 0;
}

uint8_t debounceRight(sys_state stateIfDebounced){
	if (rightButton() && (debounceObj != LEFT)) {
		if (!timeout_start) { // begin debouncing right button
			timeout_start = millis();
			debounce_obj =  RIGHT;	
		} else if (timeout_curr >= debounce_time){ // debounce complete
			timeout_start = 0;
			debounceObj = NULL;
			return 2;
		}
		return 1;
	}
	return 0;
}

// bool debounceLeft(sys_state stateIfDebounced){
// 	if (leftButton() && (debounceObj != RIGHT)) {
// 		if (!timeout_start) { // begin debouncing left button
// 			timeout_start = millis();
// 			debounce_obj =  LEFT;	
// 		} else if (timeout_curr >= debounce_time){ // debounce complete
// 			timeout_start = 0;
// 			sysState = stateIfDebounced;
// 		}
// 		return 1;
// 	}
// 	return 0;
// }

// bool debounceRight(sys_state stateIfDebounced){
// 	if (rightButton() && (debounceObj != LEFT)) {
// 		if (!timeout_start) { // begin debouncing right button
// 			timeout_start = millis();
// 			debounce_obj =  RIGHT;	
// 		} else if (timeout_curr >= debounce_time){ // debounce complete
// 			timeout_start = 0;
// 			sysState = stateIfDebounced;
// 		}
// 		return 1;
// 	}
// 	return 0;
// }

acceleration_axes getAcceleration(){
	return ((acceleration_axes) {CircuitPlayground.motionX(), CircuitPlayground.motionY(), CircuitPlayground.motionZ()});
}

accel_characteristic getCharacteristic(){
	int i;
	accel_characteristic curr;
	for (i = 1; i < sizeof(sampleArr); i++){
		if ((int)(sampleArr[i-1] - sampleArr[i]) > 0) { // += 

}
exercise getExercise(){

}
