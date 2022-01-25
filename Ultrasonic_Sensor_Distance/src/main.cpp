#include <Arduino.h>

// Measuring Distance with ESP32 and Ultrasonic Sensor 

// define pin variables
const int trigPin = 12;                   // Pin 12 does not chang -> const int
const int echoPin = 13;                   // Pin 13 does not change -> const int

// defines changing variables
long duration;                            // long data type for duration
float distance;                           // float data for precise xx.xxx measurement

// define variables for timer
unsigned long previousMillis = 0;         // unsigned long for timer reset because this number can reach high values
const long  interval = 1000;              // constant long varibale for the interval

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                   // Begin Serial comunication
  pinMode(trigPin, OUTPUT);               // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);                // Sets the echoPin as an Input
 

}

void loop() {
  // put your main code here, to run repeatedly:
  
  unsigned long currentMillis = millis();               // starts the millis timer from 0
  
  if (currentMillis - previousMillis >= interval) {     // if actual time minus previous time greater than interval
    
    previousMillis = currentMillis;                     // Take the actual time as previous time
    
    digitalWrite(trigPin, LOW);                         // Clears the trigPin
    delayMicroseconds(2);                               // delay for 2 microseconds

    
    digitalWrite(trigPin, HIGH);                        // Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(10);                              // wait 10 microseconds
    digitalWrite(trigPin, LOW);                         // Set triger pin low again

    
    duration = pulseIn(echoPin, HIGH);                   // pulseIn Reads the echoPin and returns the sound wave travel time in microseconds

    
    distance = duration * 0.034 / 2;                      // Calculating the distance: time * speed of sound per microsecond / halfway

    
    Serial.print("Distance: ");                           // Prints the distance in "cm" on the Serial Monitor
    Serial.print(distance);
    Serial.println(" cm");
    
  }
}