/*#include <Arduino.h>


const int btn1Pin = 18;
const int btn2Pin = 19;
const int ledGrn = 12;
const int ledGlb = 13;
const int ledRot = 14;
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


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  pinMode(btn1Pin, INPUT_PULLUP);
  pinMode(btn2Pin, INPUT_PULLUP);
  pinMode(ledGrn, OUTPUT);
  pinMode(ledGlb, OUTPUT);
  pinMode(ledRot, OUTPUT);

}

void blinken() {
{
  digitalWrite(ledGrn, !(millis() % 1000 >= 500));
  digitalWrite(ledRot, millis() % 1000 >= 500);
} 

}

void loop() {

    byte btn1State = digitalRead(btn1Pin);

    if ((millis() - time) > bounce) {
        time = millis();
        if (btn1State != last_btn1State) {
            last_btn1State = btn1State;

            if (btn1State == LOW) {
                trigger = !trigger;
            
            }
        } 
    } if (trigger == HIGH) {
    blinken();
    } else if (trigger == LOW) {
    digitalWrite(ledGrn, LOW);
    digitalWrite(ledRot, LOW);
    
}
// digitalWrite(ledGrn,ledState);
    Serial.println(trigger);
}*/