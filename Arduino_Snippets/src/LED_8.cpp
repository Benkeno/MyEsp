#include <Arduino.h>

const int led1 = 12;
const int led2 = 27;
const int led3 = 16;
const int led4 = 13;
const int led5 = 14;
const int led6 = 17;
const int led7 = 25;
const int led8 = 26;
const int ledNummer = 8;
int lichtPin = 4;
int lichtWert = 0;

byte LEDPinArray[ledNummer] = { led1,led2,led3,led4,led5,led6,led7,led8 };

void setup() {
    Serial.begin(115200);

    pinMode(lichtPin, INPUT);

    for (int i = 0; i < ledNummer; i++) {
        pinMode(LEDPinArray[i], OUTPUT);
    }

}

void loop() {

    int lichtWert = analogRead(lichtPin);
    int lichtMap  = map(lichtWert, 0,2500,0,7);

    for (int i = 0; i < lichtMap; i++) {
       digitalWrite(LEDPinArray[i], HIGH);
    }
    for (int i = 7; i >= lichtMap; i--) {
       digitalWrite(LEDPinArray[i], LOW);
    }
    Serial.println(lichtWert);
    Serial.println(lichtMap);
    delay(10);
}