#include <Arduino.h>


void flash_led(){
    while (1)
    {   
        Serial.println("ON");
        digitalWrite(22, HIGH);   // turn the LED off by making the voltage LOW
        delay(1000);
        digitalWrite(22, LOW);   // turn the LED off by making the voltage LOW
        delay(1000);
    }
    return;
}