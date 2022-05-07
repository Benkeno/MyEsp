#include <Arduino.h>



unsigned long timestamp = 0;                                    // declare the variable to save the time
const int ledPin = 2;                                           // variable ledPin for GPIO 2 
int interval = 1000;                                            // the variable interval in milliseconds
byte ledPinState = LOW;                                         // variable to hold the Pinstatus 

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);                                          // initialze the serial com port on the ESP board with the .begin(baudrate) function
  Serial.print("Hello World !");                                 // print a new line on the serial console with a string "Hello World" for greeting
  pinMode (LED_BUILTIN, OUTPUT);                                      // set GPIO PIN 2 as output
}

void loop() {
  // put your main code here, to run repeatedly:

   unsigned long currentmillis = millis();                       // starts a timer counting up in millisecs

  if (currentmillis - timestamp >= interval) {                  // if the counted time - the timestamp (difference) is greater than interval ?
    if (ledPinState == LOW) {                                   // check if ledPinState is LOW ?
      ledPinState = HIGH;                                       // set ledpinstate to HIGH
      Serial.println("LED is ON");                              // print Info for debugging
      }
      else {                                                      
        if (ledPinState == HIGH) {                              // check if ledPinState is HIGH ?
          ledPinState = LOW;                                    // set ledpinstate to LOW
          Serial.println("LED is OFF");                         // print Info for debugging
        }
    }

    timestamp = currentmillis;                                  // timestamp becomes the count of time from currentmillis
    digitalWrite(LED_BUILTIN, ledPinState);                          // update the ledPin with the actual ledPinState
    Serial.println(timestamp);                                  // to see the timestamp changes !
  
  }
}