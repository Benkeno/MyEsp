/*#include <Arduino.h>

const int led1 = 26;
const int led2 = 25;
const int led3 = 17;
const int led4 = 16;
const int led5 = 27;
const int led6 = 14;
const int led7 = 12;
const int led8 = 13;
const int led9 = 5;
const int ledNummer = 9;
const int lichtSensorPin = 4;
//const int btn1Pin = 18;
//const int btn2Pin = 19;

int timestamp = 0;
int timestamp2 = 0;
long interval = 1000;
int hinUndHer = 0;

int ledMap; 
int lichtWert;
int ledCount = 0;
int step =1;
unsigned long millis();

byte LEDPinArray[ledNummer] = { led1,led2,led3,led4,led5,led6,led7,led8,led9 };


//void levelMeter() {
//}

void setup() {
    Serial.begin(115200);

    pinMode(lichtSensorPin, INPUT);
    //pinMode(btn1Pin, INPUT_PULLUP);
    //pinMode(btn2Pin, INPUT_PULLUP);

    for (int p = 0; p < ledNummer; p++) {
        pinMode(LEDPinArray[p], OUTPUT);
        Serial.println(LEDPinArray[p]);
    }

}

void loop() {

    unsigned long millis();

        

     int lichtWert = analogRead(lichtSensorPin);
    
    int ledMap  = map(lichtWert, 0,4095,1,9);

    for (int i = 0; i < ledMap; i++) {
       digitalWrite(LEDPinArray[i], HIGH);
           
    }
    for (int i = 9; i >= ledMap; i--) {
       digitalWrite(LEDPinArray[i], LOW);
       
       
    }
 /*
    for (int i = 0; i < ledMap; i++) {
       digitalWrite(LEDPinArray[i], HIGH);
       digitalWrite(LEDPinArray[i-1], LOW);
           
    }    
    
    for (int i = 9; i >= ledMap; i--) {
       digitalWrite(LEDPinArray[i], LOW);
       digitalWrite(LEDPinArray[i-1], HIGH);
       
     } 
*/
    /*
    int hinUndHer = map(lichtWert,1800,4095,10,300);
    if ((millis() - timestamp) > hinUndHer) {
    timestamp = millis();  
   
    //Serial.print("ledcounter: ");
    //Serial.println(ledCount);
    ledCount = ledCount + step;
    if (ledCount >=9 || ledCount <=0) {
        step =  -step;
    }
    for (int i = 0; i < ledCount; i++) {
       digitalWrite(LEDPinArray[i], HIGH);
       digitalWrite(LEDPinArray[i-1], LOW);
           
    }  
    for (int i = 9; i >= ledCount; i--) {
       digitalWrite(LEDPinArray[i], LOW);
       digitalWrite(LEDPinArray[i-1], HIGH);
       
     } 
    */ 
    if ((millis() - timestamp2) > interval) {
    timestamp2 = millis();  
   
    
    Serial.print("ledMap: ");
    Serial.println(ledMap);
    }
    }
*/