# Workout Routine Monitor

## Description

This program monitors and displays the progress of a user's workout routine using an Adafruit Circuit Playground Classic or Express. 

This program uses the Adafruit Circuit Playground Library. To learn how to install this library, visit the [GitHub repository](https://github.com/adafruit/Adafruit_CircuitPlayground). 

## Usage

The Circuit Playground board should be strapped to the user's left upper arm. It should be positioned so that the y-axis points toward the hand and the z-axis points away from the body. 

[Image coming soon]

### Changing Workout Routine Length

By default, there are 10 repetitions of each exercise in the workout routine. If the workout routine has not begun (i.e. no exercises have been completed or are in the process of being completed), the user is allowed to change the number of repetitions for each exercise (up to 40). 

The steps to change the number of repetitions are:
1. Ensure that the program status is "ready" (see subsection "System Status" in "Reading the LEDs" for more information)
2. Press the bottom button (closest to the shoulder)
3. The user will be taken to a new "page" of LEDs that displays the number of repetitions selected (see subsection "Repetition Select Page" in section "LED Pages" for more information)
4. To increase the number of repetitions, press the top button (closest to the hand). To decrease the number of repetitions, press the bottom button (closest to the shoulder).
5. Repeat step 4 until the desired number of repetitions is reached.
6. Do not press any buttons for four seconds, and it will return to the "ready" page. 

### Beginning an Exercise

Exercises may be completed in any order. 

The steps to begin an exercise are:
1. Ensure that the program status is "ready" (see subsection "System Status" in "Reading the LEDs" for more information)
2. Press the top button (closest to the hand) 
3. Ensure that the program status is "measuring"(see subsection "System Status" in "Reading the LEDs" for more information)
4. Begin exercise

If an excercise cannot be identified within four seconds, the program status will display an error for four seconds before returning to the ready page.

Once an exercise has been identified, the status LED will become the color of the identified exercise. As the exercise is completed, the LEDs will fill counter-clockwise from (and including) the status LED according to the percentage of the exercise completed. 

Once an exercise is completed, the LEDs will turn white for four seconds then it will return to the ready page.

### Exiting an Exercise

There is no time limit for completing each exercise. If the user no longer wishes to finish an exercise, they can exit out. 

To exit an exercise:
1. Ensure that the program status is either "measuring" or an identified exercise (see subsection "System Status" in "Reading the LEDs" for more information)
2. Press and hold the top button (closest to the hand) for two seconds
3. The user will be returned to the "ready" page

### Resetting a Routine

There is no time limit for completing a workout routine. If the user no longer wishes to finish a routine, they can press and hold the board's "reset" button to reset the device. 

If the user has completed a workout routine and the program status LED is white, they can press and hold the board's "reset" button to begin a new routine. 


## Reading the LEDs

The LEDs of the Circuit playground are set up with the user's perspective in mind. When the user is looking down at the board, the row of LEDs closest to the hand appears to be the top of the board, and so is referred to in this document as the "top row."

[Image coming soon]

### Status LEDs

The top row consists of the Status LEDs. These LEDs are visible on the ready page and the measuring page. 

### Program Status LED

The first LED of the top row (on the far right) is the program status LED. This LED will have different colors depending on the status of the routine. 

The colors and definitons of the program status LED are:
- Ready: Green
- Measuring: Red
- In progress: The exercise color
- Complete: White
- Error: Red

### Exercise LEDs

The second through fifth LEDs in the top row are the completed exercise LEDs. Going counter-clockwise from the program status LED, the order is: first exercise, second exercise, third exercise, and fourth exercise. Each LED will be the color of the exercise completed.

The colors of the exercises are:
- Sit up: Orange
- Jumping jack: Cyan
- Push up: Purple
- Squat: Pink

Once an exercise is completed, the LEDs will turn white for 4 seconds then it will return to the "ready" menu.


## LED Pages

Depending on the state of the program, there are several different "pages" of information that the status LEDs can represent. 

### Ready Page

This page displays the status LEDs, with the program status LED being green.

### Repitition Select Page

This page displays the number of repetitons chosen. Each LED represents one repition, and the LED colors represent how many groups of ten have passed.

The LED colors are:
- Zero: Orange
- Ten: Yellow
- Twenty: Cyan
- Thirty: Purple

For example, if the LED color is cyan and three LEDs are lit, then the number of repetitions is twenty-three. 
Another example, if the LED color is orange and ten LEDs are lit, then the number of repetitions is ten. If the top button is pressed once to make 11 repeitions, the LED color will change to yellow and only one LED will be lit.

### Measuring Page

This page displays the status LEDs, with the program status LED being blue.

### Error Page

This page displays the status LEDs, with the program status LED being red.

### Exercise In Progress Page

All LEDs on this page are the corresponding exercise color. The ten LEDs represent the percentage of repeitions completed for the exercise. Each LED represents 10% of the exercise, and a single LED will be lit if less than and up to that percentage is complete. 

For example, if 10% or less is complete, then only the first LED will be list. If less than 20% but more than 10% is complete, then the first two LEDs will be lit.

When 100% of the exercise is complete, the LEDs will turn white for two seconds before returning to the ready page.

### Workout Complete Page

This page displays the status LEDs, with the program status LED being white.


## Author

This program was written by Melissa Jacob as the Embedded Challenge (term project) for ECE-UY 4144 in Fall 2020.
