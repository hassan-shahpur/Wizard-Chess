/**
 * @brief Controls the movement of the gantry
 * @details Methods that move the gantry in different amounts to the necessasry squares
 * @authors
*/

#include "steppers.hpp"
#include <Arduino.h>
#include "definitions.hpp"
#include <iostream>
#include <cstdlib>


/**
 * @brief Moves in the x direction by one step
 * @details 
 * @param direction The diection to move. 0 for negative, 1 for positive
 */
void steppers::tick_x(int direction){
  
  if(direction == 0){
    set_stepper(0, 0);
    set_stepper(1, 0);
    delay(DELAY);
    set_stepper(0, 1);
    set_stepper(1, 1);
    delay(DELAY);
  }
  if(direction == 1){
    
    //Move A counter clockwise
      set_stepper(2, 0);
      delay(1);
      set_stepper(3, 0);  
      delay(1);
    
    set_stepper(0, 0);

    //Move B counter clockwise
    set_stepper(2, 1);
    delay(1);
    set_stepper(3, 1);  
    delay(1);

    set_stepper(0, 1);
    
    
  }
}

/**
 * @brief Moves in the y direction by one step
 * @details 
 * @param direction The diection to move. 0 for negative, 1 for positive
 */
void steppers::tick_y(int direction){
  if(direction == 0){
    set_stepper(0, 0);
    set_stepper(1, 0);
    delay(DELAY);
    set_stepper(2, 1);
    set_stepper(3, 1);
    delay(DELAY);
  }
  if(direction == 1){
    set_stepper(2, 0);
    set_stepper(3, 0);
    delay(DELAY);
    set_stepper(0, 1);
    set_stepper(1, 1);
    delay(DELAY);
  }
}

/**
 * @brief Set the stepper motor
 * @details A step is made by setting the motor high, then low
 * @param value The value to set the motor to. High or low
 * @param motor The motor to tick. 0 is A, 1 is B
 */
void steppers::set_stepper(int value, int motor){
  // if row is 0, write to x, else write to y
  // Figure out what pins to set
  bool first_digit = value & 0x01;
  bool second_digit = (value >> 1) & 0x01;

  int pin0;
  int pin1;
  if(motor == 0){
    pin0 = PIN_A1;
    pin1 = PIN_A2;
  }else{
    pin0 = PIN_B1;
    pin1 = PIN_B2;
  }
  // Write to all pins
  if(first_digit){
    digitalWrite(pin0, HIGH);
  }else{
    digitalWrite(pin0, LOW);
  }
  if(second_digit){
    digitalWrite(pin1, HIGH);
  }else{
    digitalWrite(pin1, LOW);
  }
  // Serial.println();
}

steppers::steppers(bool verbose) {}

/**
 * @brief Reset position of stepper to find position
 * @details Make the gantry hit two corners to find the x and the y axis so we have the values of both stored
*/
void steppers::zero_steppers(){
  
  while(analogRead(PIN_LIMIT1) < 2000){
    // while(1){
    //std::cout << "Y: " << analogRead(PIN_LIMIT1) << std::endl;
    tick_y(1);
  }
  for(int i = 0; i < 20; i++){
    tick_y(0);
  }
  
  while(analogRead(PIN_LIMIT2) < 2000){
    tick_x(1);
    //delay(10);
  }
  for(int i = 0; i < 20; i++){

    tick_x(0);
    //delay(1);
  }

  //test();

  

}

/**
 * @brief Move stepper to coordinate
 * @details
 * @param int how far to moxe on the x axis
 * @param int how far to moxe on the x axis
*/
void steppers::move_to(int x_dist, int y_dist){
  
  int delta_x = x_dist - this->current_x;
  int delta_y = y_dist - this->current_y;
  Serial.println("DX: " + delta_x);
  Serial.println("DY: " + delta_y);
  // Move up
  if(delta_y > 0){
    for(int i = 0; i < delta_y; i++){
      tick_y(1);

    }
  }else{
    for(int i = 0; i < -1*delta_y; i++){
      tick_y(0);
    }
  }
  
  if(delta_x > 0){
    for(int i = 0; i < delta_x; i++){
      tick_x(1);
    }
  }else{
    for(int i = 0; i < -1*delta_x; i++){
      tick_x(0);
    }
  }

  this->current_x = x_dist;
  this->current_y = y_dist;


  // for(int i = 0; i < delta_x; i += DISTANCE_RATIO){
  //   tick_x(0);
  // }
  
  // for(int i = 0; i < delta_y; i += DISTANCE_RATIO){
  //   tick_y(0);
  // }

  
}

/**
 * @brief Move the piece
 * @details
 * @param string move selected
*/
bool steppers::make_move(std::string move) {
    // Knight moves are distinct from other pieces
    // Knight's move's are "L" shape
    char files[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int oldFile, newFile;
    int rankDiff, fileDiff;
    bool knightMove;
    // get the file values from move
    for (int i = 0; i < 8; i++) {
      if (move[0] == files[i]) oldFile = i;
      if (move[2] == files[i]) newFile = i;
    }
    // get the number of files moved 
    fileDiff = newFile - oldFile;
    // get the number of ranks moved
    rankDiff = move[1] - move[3];
    if (abs(fileDiff) > 0 && abs(rankDiff) > 0 && abs(abs(fileDiff) - abs(rankDiff)) == 1) {
      knightMove = true;
    } else {
      knightMove = false;
    }

    if(knightMove){
      float x_dist = BOARD_X_OFFSET + SQUARE_WIDTH * move[3];
      float y_dist = BOARD_X_OFFSET + SQUARE_WIDTH * oldFile;
      move_to(x_dist, y_dist);
      
      
      x_dist = BOARD_X_OFFSET + SQUARE_WIDTH * move[0];
      y_dist = BOARD_X_OFFSET + SQUARE_WIDTH * newFile;
      move_to(x_dist, y_dist);
      digitalWrite(PIN_ELECTROMAGNET, LOW);

    }else{
      float x_dist = BOARD_X_OFFSET + SQUARE_WIDTH * move[3];
      float y_dist = BOARD_X_OFFSET + SQUARE_WIDTH * oldFile;
      move_to(x_dist, y_dist);
      digitalWrite(PIN_ELECTROMAGNET, HIGH);
      
      x_dist = BOARD_X_OFFSET + SQUARE_WIDTH * move[0];
      y_dist = BOARD_X_OFFSET + SQUARE_WIDTH * newFile;
      move_to(x_dist, y_dist);
      digitalWrite(PIN_ELECTROMAGNET, LOW);

    }

    return false;
}

void steppers::test(){

  // for(int i = 0; i < 200; i++){
  //   set_stepper(0, 0);
  //   set_stepper(1, 0);
  //   delay(DELAY);
  // }
  // for(int i = 0; i < 200; i++){
  //   set_stepper(2, 0);
  //   set_stepper(3, 0);
  //   delay(DELAY);
  // }
  // for(int i = 0; i < 200; i++){
  //   set_stepper(0, 0);
  //   set_stepper(1, 0);
  //   delay(DELAY);
  // }
  // for(int i = 0; i < 200; i++){
  //   set_stepper(2, 0);
  //   set_stepper(3, 0);
  //   delay(DELAY);
  // }

  for(int i = 0; i < 200; i++){
    tick_y(0);
    delay(DELAY);
  }
  for(int i = 0; i < 200; i++){
    tick_x(0);
    delay(DELAY);
  }
  for(int i = 0; i < 200; i++){
    tick_y(1);
    delay(DELAY);
  }
  for(int i = 0; i < 200; i++){
    tick_x(1);
    delay(DELAY);
  }
  
  // for(int i = 0; i < 300; i++){
  //   tick_x(1);
  // }
  // for(int i = 0; i < 300; i++){
  //   tick_y(1);
  // }
  // for(int i = 0; i < 300; i++){
  //   tick_x(0);
  // }
  // for(int i = 0; i < 300; i++){
  //   tick_y(0);
  // }

}
