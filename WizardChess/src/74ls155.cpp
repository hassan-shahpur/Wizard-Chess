
// #include <Arduino.h>
// #include "flash.h"

// #define A 19
// #define B 21
// #define C1 22
// #define C2 23

// #define DELAY 1000


// void set(bool a, bool b){
//   if(a){
//     digitalWrite(A, HIGH);
//   }else{
//     digitalWrite(A, LOW);
//   }
//   if(b){
//     digitalWrite(B, HIGH);
//   }else{
//     digitalWrite(B, LOW);
//   }
  
// }

// bool top = false;

// // the setup function runs once when you press reset or power the board
// void setup() {
//   // initialize digital pin LED_BUILTIN as an output.
//   Serial.begin(9600);
  
//   pinMode(A, OUTPUT);
//   pinMode(B, OUTPUT);
//   pinMode(C1, OUTPUT);
//   pinMode(C2, OUTPUT);
  
// }

// // the loop function runs over and over again forever
// void loop() {
//   // flash_led();
  
//   if(top == false){
//     digitalWrite(C1, LOW);
//     digitalWrite(C2, HIGH);
    
//   }else{
//     digitalWrite(C1, HIGH);
//     digitalWrite(C2, LOW);
//   }
//   top = !top;
//   Serial.println(top);
//   delay(DELAY);
//   set(false, false);
//   delay(DELAY);
//   set(true, false);
//   delay(DELAY);
//   set(false, true);
//   delay(DELAY);
//   set(true, true);
  
//   // Serial.println("0:");
//   // digitalWrite(A, LOW);
//   // digitalWrite(B, LOW);
//   // digitalWrite(C, LOW);
//   // delay(DELAY);
  
// }
