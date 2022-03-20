#include <Arduino.h>

#define VOLTSENSOR_PIN 36
#define VOLTSENSOR_VOLTAGE 3.33f




const float R1 = 30500.0f;
const float R2 = 7500.0f;
const float Vref = VOLTSENSOR_VOLTAGE;



void setup() {
  // Begin Serial Communication for Debugging and Output to Terminal
  Serial.begin(115200);
  // Set PIN variable to input mode
  pinMode(VOLTSENSOR_PIN, INPUT);
  
  
  
}

void loop() {

  // Set U as variable that returns a float datatype from the Sensor pin and calculate 
  
  float val = analogRead(VOLTSENSOR_PIN)* Vref /4095.0f;
  float valin = val / (R2/(R1+R2));
  Serial.print("Batteriespannung: ");  // Text to display
  Serial.print(valin);            // Text the variable name wich contains the calculated float value
  Serial.println(" Volt");
  delay(1000);
   
}