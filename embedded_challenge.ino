// Melissa Jacob - mrj310 - Embedded Challenge Fall 2020
// main file

#include <Adafruit_CircuitPlayground.h>
#include "embedded_challenge.h"
#include "functions.h"

// other (global) variables found in global.h
int i, j, k; // loop variables

sys_state sysState; // system state 

// vars for exeercise tracking
int repetitionsRequired;  // the number of repetitions in each exercise
int repetitionsCompleted; // number of repetitions for currExercise

void setup() {
  Serial.begin(9600);
  // Instead of setting up individual timers, millis will be used to 
  // determine if a certain time has passed
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(5);
  
  repetitionsRequired = 10; // default exercise length
  currExercise = 0;
 for (i = 0; i < 4; i++){
   exerciseArr[i] = NULL_EXERCISE; 
 }
  // exerciseArr[0] = PUSH_UP;
  // exerciseArr[1] = SIT_UP;
  // exerciseArr[2] = SQUAT;
  // exerciseArr[3] = JUMPING_JACK;
  Serial.println("B");
  sysState = RESET_EXERCISE;

}

void loop() {
//updateDisplay_statusLEDs(READY_COLOR);
switch(sysState){
   case RESET_EXERCISE:
     Serial.println("RESET_EXERCISE");
     //currPercentChar = {0,0,0};
     debouncing = NONE;
     startTime = 0;
     currTime = 0;

     displayColor = OFF_COLOR;
     displayNum = 0;
     
     currAccel = NULL_ACCEL_AXES;
     prevAccel = NULL_ACCEL_AXES;
     measuredExercise = NULL_EXERCISE;

     exerciseArr[currExercise] = NULL_EXERCISE;
     repetitionsCompleted = 0;
     sampleCount = 0;

     sysState = READY;
     break;

   case READY:
     // Serial.println("READY");
     
     updateDisplay_statusLEDs(READY_COLOR);

     setCurrTime();
      //Serial.println(debouncing);
     if (checkRightDebounce() == 2) // if right debounce completed
       sysState = CHANGE_REPETITIONS;
     else if (checkLeftDebounce() == 2) // if left debounce completed
       sysState = MEASURING;
     // if debounce not completed and debounce time is up
     else if (debouncing && currTime >= debounce_time) { 
       debouncing = NONE;
       startTime = 0;
     }
     break;

   case CHANGE_REPETITIONS:
     if((displayNum = (repetitionsRequired % 10)) == 0)
       displayNum = 10;

     if (repetitionsRequired <= 10) 
       displayColor = ONES_COLOR;
     else if (repetitionsRequired <= 20)
       displayColor = TENS_COLOR;
     else if (repetitionsRequired <= 30)
       displayColor = TWENTIES_COLOR;
     else displayColor = THIRTIES_COLOR; 

     updateDisplay_oneColor();
     setCurrTime();
     //Serial.println(debouncing);
     if ((checkLeftDebounce() == 2) && (repetitionsRequired < 40)) 
       repetitionsRequired++;
     else if ((checkRightDebounce() == 2) && (repetitionsRequired > 1))
       repetitionsRequired--;
     // if debounce not completed and debounce time is up
     else if (debouncing && (currTime >= debounce_time)) {
       debouncing = NONE;
       startTime = millis();
     }
     // if no debounce is happening & no buttons pressed for 4 seconds
     else if (!debouncing && (currTime >= four_sec_timeout)) {
       startTime = 0;
       sysState = READY;
     }
     break;

   case MEASURING:
     updateDisplay_statusLEDs(MEASURING_COLOR);
     setCurrTime();
     if (checkLeftDebounce() == 2)
       sysState = RESET_EXERCISE;
     else if (debouncing && (currTime >= debounce_time)){
       debouncing = NONE;
       startTime = 0;
     }
    else if (!debouncing) { // measure movement
      if (!startTime) 
        startTime = millis();
      else if (currTime >= sample_time){
         getAcceleration();
         if (prevAccel != NULL_ACCEL_AXES){        
          getExercise();
           Serial.print("exercise ");
           if(measuredExercise== NULL_EXERCISE)
              Serial.println("NULL");
           if(measuredExercise == PUSH_UP)
              Serial.println("PUSH_UP");
           if(measuredExercise == SIT_UP)
              Serial.println("SIT_UP");
           if(measuredExercise == SQUAT)
              Serial.println("SQUAT");
           if(measuredExercise == JUMPING_JACK)
              Serial.println("JUMPING_JACK");
          }
         prevAccel = currAccel;
         startTime = 0;
       }
       if (sampleCount == measuring_sample_size){
         exerciseArr[currExercise] = measuredExercise;
         repetitionsCompleted++;
         startTime = 0;
         sysState = EXERCISE_IN_PROGRESS;
       }
     }
     break;

   case EXERCISE_IN_PROGRESS:
     displayColor = exerciseArr[currExercise].color;
     displayNum = (repetitionsCompleted*10)/repetitionsRequired;
     updateDisplay_oneColor();

     setCurrTime();
     if (checkLeftDebounce() == 2)
       sysState = RESET_EXERCISE;
     else if (debouncing && (currTime >= debounce_time)){
       debouncing = NONE;
       startTime = 0;
     }
     else if (!debouncing) { // count movements
      if (!startTime) 
        startTime = millis();
      else if (currTime >= sample_time){
        getAcceleration();        
        getExercise();
        prevAccel = currAccel;
        startTime = 0;
       }
      if (sampleCount == in_progress_sample_size)
         repetitionsCompleted++;
      if (repetitionsCompleted == repetitionsRequired){
        currExercise++;
        startTime = millis();
        sysState = EXERCISE_COMPLETE;
       }
     }
     break;

   case EXERCISE_COMPLETE:
     displayColor = COMPLETE_COLOR;
     displayNum = 10;
     updateDisplay_oneColor();
     setCurrTime();
     if (currExercise == 4)
        sysState = ROUTINE_COMPLETE;
     if (currTime >= four_sec_timeout)
       sysState = RESET_EXERCISE;
     break;

   case ROUTINE_COMPLETE:
     updateDisplay_statusLEDs(COMPLETE_COLOR);
     break;
   }
}
