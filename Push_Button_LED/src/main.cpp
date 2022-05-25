// If a Button is pushed the ESP32 Onboard LED will light up //


#include <Arduino.h>

const int buttonPin = 18;
const int ledPin = 36;
int buttonState = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  // read the state of the pushbutton value and store it in buttonState:
  buttonState = digitalRead(buttonPin);

    // check if the pushbutton is pressed. e.g. the buttonState is HIGH:
    if (buttonState == LOW) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);  
      Serial.println("Button ist LOW und die Led ist AN");
    } else {
      // turn LED off:
        digitalWrite(ledPin, LOW);
        Serial.println("Button ist HIGH und die Led ist AUS");
    }

}