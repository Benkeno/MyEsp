/*#include <Arduino.h>

const int xPotiPin = 34;
const int yPotiPin = 35;

int xPoti = 0;
int yPoti = 0;
int xGain = 1;
int yGain = 1;
int timestamp1 = 0;

void setup() {
    Serial.begin(115200);
    pinMode(xPotiPin, INPUT);
    pinMode(yPotiPin, INPUT);

}

void loop() {

int xPoti = analogRead(xPotiPin);
int yPoti = analogRead(yPotiPin);

if ((millis() -timestamp1) > 1000) {
        timestamp1 = millis();
        Serial.print("X-Achse: ");
        Serial.println(xPoti);
        Serial.print("Y-Achse: ");
        Serial.println(yPoti);
      } 

}*/