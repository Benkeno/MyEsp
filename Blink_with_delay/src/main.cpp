#include <Arduino.h>

int led = 2;

void setup() {
                                              // put your setup code here, to run once:
  Serial.begin(115200);                       // initialze the serial com port on the ESP board with the .begin(baudrate) function
  Serial.print("Blink with 1 sec delay");     // print a new line on the serial console with a string "Hello World" for greeting
  pinMode (led, OUTPUT);                        //Specify that GPIO 2 pin is output (on ESP32 GPIO2 is internal conected with the blue onBoard LED)

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(led,HIGH);                       // set pin 2 to High (3.3V)
  delay(1000);                                // freeze for 1000 milliseconds
  digitalWrite(led,LOW);                        // set pin 2 to LOW (0.8V)
  delay(1000);                                // freeze for 1000 milliseconds
}