#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Measuring Distance with ESP32 and Ultrasonic Sensor !
// Three different ranges are indicated by 3 LEDs 

// define pin variables
const int trigPin = 12;                   // Pin 12 does not chang -> const int
const int echoPin = 13;                   // Pin 13 does not change -> const int
const int gruenLED = 17;
const int gelbLED = 26;
const int rotLED = 25;
const int ledZahl = 3;

int distanzToAmpel;


byte LEDPinArray[ledZahl] = { rotLED, gelbLED, gruenLED  };
LiquidCrystal_I2C lcd(0x27,16,2);

// defines changing variables
long duration;                            // long data type for duration
double distance;                           // double data for precise xx.xxx measurement


// define variables for timer
unsigned long timestamp = 0;         // unsigned long for timer reset because this number can reach high values
unsigned long timestamp2 = 0;
unsigned long timestamp3 = 0;
const long  interval = 200;              // constant long varibale for the interval


void distanzMessen() {

  unsigned long currentMillis = millis(); 

    if (currentMillis - timestamp >= interval) {     // if actual time minus previous time greater than interval
    
      timestamp = currentMillis;                     // Take the actual time as previous time
      digitalWrite(trigPin, LOW);                         // Clears the trigPin
      delayMicroseconds(2);                               // delay for 2 microseconds
      digitalWrite(trigPin, HIGH);                        // Sets the trigPin on HIGH state for 10 micro seconds
      delayMicroseconds(10);                              // wait 10 microseconds
      digitalWrite(trigPin, LOW);                         // Set triger pin low again
    
      duration = pulseIn(echoPin, HIGH);                   // pulseIn Reads the echoPin and returns the sound wave travel time in microseconds
    
      distance = duration * 0.034f / 2;                      // Calculating the distance: time * speed of sound per microsecond / halfway

      char distString[8];                                   // initialize char array (8) index
      dtostrf(distance, 5, 1, distString);                // convert float to string for display (Float, digits, dezimals, FloatAsString)
    
      if (currentMillis - timestamp2 >= 800) {              // if actual time minus previous time greater than interval
        timestamp2 = currentMillis;                         // new timestamp with currenttime
        
        if (distance < 120.00f) {
            lcd.setCursor(0,0);                             // show "----"
            lcd.print("  ! MESSUNG ! ");
            lcd.setCursor(0,1);                           // set cursor block 0, row 1 (2. reihe)
            lcd.print("Distanz:");
            lcd.print(distString);                        // print  the String
            lcd.print(" cm");
            }

        if (distance >= 120.00f) {                      // if distance greater or equal 120cm 
            lcd.setCursor(0,0);                             // show "----"
            lcd.print("Genug Platz...");
            lcd.setCursor(0,1);                             // show "----"
            lcd.print("Distanz: ---- ");
            }        
      }

    }

}

void ledAmpel() {

   int distanzToAmpel = map (distance, 2, 30, 0,2);

  for (int i = 0; i < distanzToAmpel; i++) {
       digitalWrite(LEDPinArray[i], LOW);
           
    }
    for (int i = 2; i >= distanzToAmpel; i--) {
       digitalWrite(LEDPinArray[i], HIGH);
       
      }
}



void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Distanz messen");
  
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);               // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);                // Sets the echoPin as an Input

  for (int p = 0; p < ledZahl; p++) {
        pinMode(LEDPinArray[p], OUTPUT);
        
    }
  delay(2000);
  lcd.clear();
}



void loop() {

  distanzMessen();
  ledAmpel();

}