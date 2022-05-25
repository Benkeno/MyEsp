/*#include <Arduino.h>


const int btn1Pin = 18;
const int btn2Pin = 19;
const int ledGrn = 12;
const int ledGlb = 13;
const int ledRot = 14;
int ledNumber = 3;
byte btn1State = HIGH;
byte last_btn1State;
byte btn2State = HIGH;
byte last_btn2State;
byte trigger = 0;
byte ledGrnState = 0;
byte ledGlbState = 0;
byte ledRotState = 0;
unsigned long time = 0;
int bounce = 20;
byte LEDPinArray[ledNumber] = { ledRot,
                                 ledGlb,
                                 ledGrn, }

void setup()
{
  for (int i = 0; i < ledNumber; i++) {
    pinMode(LEDPinArray[i], OUTPUT);
  }
}*/