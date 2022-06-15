/*#include <Arduino.h>

const int ledGrn = 12;
const int ledBlu = 13;
const int ledRot = 14;
const int button1Pin = 26;
const int button2Pin = 25;
const int button3Pin = 17;


byte btn1State = HIGH;
byte last_btn1State;
byte btn2State = HIGH;
byte last_btn2State;
byte btn3State = HIGH;
byte last_btn3State;
int hellRot = 0;
int hellGrn = 0;
int hellBlu = 0;
int dimmerRot = 5;
int dimmerGrn = 5;
int dimmerBlu = 5;

unsigned long bounce = 15;
int timestamp1 = 0;
int timestamp2 = 0;
int timestamp3 = 0;
int timestamp4 = 0;

void dimmen() {
  

  byte btn1State = digitalRead(button1Pin);
    byte btn2State = digitalRead(button2Pin);
    byte btn3State = digitalRead(button3Pin);
    
    if (btn1State == LOW) {
      

      if ((millis() -timestamp1) > 15) {
        timestamp1 = millis();
        analogWrite(ledGrn, hellGrn);
        hellGrn = hellGrn + dimmerGrn;
        if (hellGrn >= 255 || hellGrn <= 0) {
        dimmerGrn = -dimmerGrn; 
        } 
      } 
    } 

    
    if (btn2State == LOW) {
      
      if ((millis() -timestamp2) > 15) {
        timestamp2 = millis();
        analogWrite(ledRot, hellRot);
        hellRot = hellRot + dimmerRot;
        if (hellRot >= 255 || hellRot <= 0) {
        dimmerRot = -dimmerRot; 
        } 
      }
    } 

    
    if (btn3State == LOW) {
      
      if ((millis() -timestamp3) > 15) {
        timestamp3 = millis();
        analogWrite(ledBlu, hellBlu);
        hellBlu = hellBlu + dimmerBlu;
        if (hellBlu >= 255 || hellBlu <= 0) {
        dimmerBlu = -dimmerBlu; 
        } 
      }
    } 
   
}

void setup() {
    pinMode(ledGrn, OUTPUT);
    pinMode(ledBlu, OUTPUT);
    pinMode(ledRot, OUTPUT);
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(button3Pin, INPUT_PULLUP);
    

}

void loop() {
unsigned long millis();


//dimmen();
 
}*/ 

