/*#include <Arduino.h>


const int button1Pin = 18;
const int button2Pin = 19;
const int ledGrn = 12;
int ledPinState = 0;
byte btn1State = HIGH;
byte last_btn1State;
byte btn2State = HIGH;
byte last_btn2State;
int hell = 0;
int dimmer = 5;
unsigned long bounce = 15;
int timestamp = 0;
int timestamp2 = 0;
bool dimmerOn = true;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(ledGrn, OUTPUT);

}
void dimmen() {
  

  byte btn1State = digitalRead(button1Pin);
    
    if (btn1State == LOW) {
      
      if ((millis() -timestamp2) > 50) {
        timestamp2 = millis();
        analogWrite(ledGrn, hell);
        hell = hell + dimmer;
        if (hell >= 255 || hell <= 0) {
        dimmer = -dimmer; 
        } 
      }
    } 
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(hell);
  Serial.println();
  unsigned long millis();

  byte btn2State = digitalRead(button2Pin);

if ((millis() -timestamp) > bounce) {
  timestamp = millis();
    if (btn2State != last_btn2State) {
      last_btn2State = btn2State;
  
        if (btn2State == LOW) {
        dimmerOn = !dimmerOn;
        }
    }
  }
   if (dimmerOn) {
    dimmen();
  } 
  else if (!dimmerOn) {
    analogWrite(ledGrn, 0);
  }
  
  }  */
   