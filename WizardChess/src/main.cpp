
#include "Arduino.h"
#include "definitions.hpp"
#include "steppers.hpp"
#include "game.hpp"

int distance;
float current_x;
float current_y;
game g;
steppers s = steppers(false);
bool running;


/**
 * @brief The setup function runs once when you press reset or power the board
 * 
 */
void setup() {
  
  Serial.begin(115200);

  Serial.print("Begin chess board...\n");
  pinMode(PIN_QUERY1, INPUT);
  pinMode(PIN_QUERY2, INPUT);
  pinMode(PIN_QUERY3, INPUT);
  pinMode(PIN_QUERY4, INPUT);
  pinMode(PIN_QUERY5, INPUT);
  pinMode(PIN_QUERY6, INPUT);
  pinMode(PIN_QUERY7, INPUT);
  pinMode(PIN_QUERY8, INPUT);

  pinMode(PIN_SELECT1, INPUT);
  pinMode(PIN_SELECT2, INPUT);
  pinMode(PIN_SELECT3, INPUT);

  pinMode(PIN_A1, OUTPUT);
  pinMode(PIN_A2, OUTPUT);
  pinMode(PIN_B1, OUTPUT);
  pinMode(PIN_B2, OUTPUT);

  pinMode(PIN_ELECTROMAGNET, OUTPUT);

  pinMode(PIN_LIMIT1, INPUT);
  pinMode(PIN_LIMIT2, INPUT);

  
}

/**
 * @brief The loop function runs over and over again forever. 
 * This is defined by Arduino and cannot be changed
 * 
 */
void loop() {
  
  g.start_game();
  
  s.zero_steppers();

  s.move_to(800, 800);
  delay(1000);
  s.move_to(800, 400);
  // s.move_to(0, 0);

  while(1){
        delay(1000);
        Serial.println("HEHE");
  }


}
