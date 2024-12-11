/**
 * @brief definitions class
 * @details Lists all constant definitions for use throughout the code
 * @author
*/

// This is the speed that the steppers move at
#define DELAY 1

// Define stepper motor pins
#define PIN_A1 23
#define PIN_A2 22

#define PIN_B1 32
#define PIN_B2 27

// Define button pins
#define PIN_BUTTON 20

// Define the electromagnet
#define PIN_ELECTROMAGNET 18

// Define hall effect sensor pins
#define PIN_QUERY1 16
#define PIN_QUERY2 13
#define PIN_QUERY3 12
#define PIN_QUERY4 1
#define PIN_QUERY5 2
#define PIN_QUERY6 3
#define PIN_QUERY7 4
#define PIN_QUERY8 5

#define PIN_SELECT1 17
#define PIN_SELECT2 25
#define PIN_SELECT3 26

#define PIN_LIMIT1 15
#define PIN_LIMIT2 13

// Define the boundaries for the chess board
// This way it shouldnt crash into the walls when moving
#define MAX_X 100.0
#define MAX_Y 100.0

// =================================================
#define BOARD_X_OFFSET 5.0
#define BOARD_Y_OFFSET 5.0

#define SQUARE_WIDTH 3.0

// This is the ratio between steps from the stepper, to mm. 
// This is the circumference of the pullley, divided by the number of steps per revolution, so
// 2*pi*12.22*(1.8/360) = 0.3839026223
// If you want to move x mm, follow the formula below 
// steps = (x) * 0.3839026223
#define DISTANCE_RATIO 0.3839026223
#define NUMBER_OF_TICKS_PER_SQUARE 
// =================================================