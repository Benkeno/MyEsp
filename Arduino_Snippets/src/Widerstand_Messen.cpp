/*#include <Arduino.h>

#define SENSOR_PIN 4
#define SENSOR_VOLTAGE 3.3f




const float R1 = 1000.0f;
const float R2 = 6700.0f;
const float Vref = SENSOR_VOLTAGE;



void setup() {
  // Begin Serial Communication for Debugging and Output to Terminal
  Serial.begin(115200);
  // Set PIN variable to input mode
  pinMode(SENSOR_PIN, INPUT);
 
  
  
}

void loop() {

  // Set U as variable that returns a float datatype from the Sensor pin and calculate 
  float U = analogRead(SENSOR_PIN)  * Vref / 4095.0f;
  Serial.print("Spannung (U): ");  // Text to display
  Serial.print(U,2);            // Text the variable name wich contains the calculated float value
  Serial.println(" V");            // Text the Volt word and anter new line with println
 
 //float Rvar = (R1 * (Vref-U)/U);
 float Rvar =  (U/(Vref-U))*R1;
    Serial.print("Rvar: ");  // Text to display
  Serial.print(Rvar,0);            // Text the variable name wich contains the calculated float value
  Serial.println(" OHM");
  delay(1000);

  delay(1000);
  float I = U / (R1 + R2) * 1000.0f; // getting microamperes to milliamps *1000
  Serial.print("Strom (mAh): ");  // Text to display
  Serial.print(I,3);            // Text the variable name wich contains the calculated float value
  Serial.println(" mAh");
  delay(1000);

}*/