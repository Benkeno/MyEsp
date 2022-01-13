#include <Arduino.h> // for use in Arduino IDE uncomment this line

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                       // initialze the serial com port on the ESP board with the .begin(baudrate) function
  Serial.print("Hello World !");              // print a new line on the serial console with a string "Hello World" for greeting

}

void loop() {
  // put your main code here, to run repeatedly:
}