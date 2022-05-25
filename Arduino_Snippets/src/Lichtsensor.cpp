/*#include <Arduino.h>
#define EULERNUMBER 2.718281828459
int lichtPin = 4;
int lichtWert = 0;
double lux_f = 0;
double lux_avg =0;
const int numReadings  = 10;
int readings [numReadings];
int readIndex  = 0;
long total  = 0;

void setup() {     

    pinMode(lichtPin, INPUT);
    Serial.begin(115200);
}


double getSmooth(double lux_f) { /* function smooth 
  ////Perform average on sensor readings
  double average;
  // subtract the last reading:
  total = total - readings[readIndex];
  // read the sensor:
  readings[readIndex] = lux_f;
  // add value to total:
  total = total + readings[readIndex];
  // handle index
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;

  return average;
}

float getLux(int lichtWert) {
  // This function calculates the lux by using different proximation formulas, which are
  // the result of a Excel sheet.
  float flichtWert, fresult;

  flichtWert = float(lichtWert);

  if(lichtWert>=0 && lichtWert<=155) {  // Darkness
    fresult = 0.0;
  }
  if(lichtWert>155 && lichtWert<=350) {
    // y = 0,0042273988x2 - 1,0130028488x + 55,4403759239
    fresult = 0.0042273988 * flichtWert * flichtWert - 1.0130028488 * flichtWert + 55.4403759239;
  }
  if(lichtWert>350 && lichtWert<=650) {
    // y = 11,7717399221e0,0083003710x
    fresult = 11.7717399221 * pow(EULERNUMBER, (0.0083003710 * flichtWert));
  }
  if(lichtWert>650 && lichtWert<=936) {
    // y = 0,3373539789e0,0134529914x
    fresult = 0.3373539789 * pow(EULERNUMBER, (0.0134529914 * flichtWert)) + 448.5;
  }
  if(lichtWert>980) {                 // Upper limit of measurement
    fresult = 100000.6;
  }

  return fresult;
}

void loop() {
    
        int lichtRaw = analogRead(lichtPin);
        int lichtWert  = map(lichtRaw, 0,4095,0,1023);
   
        lux_f = getLux(lichtWert);      // Use mathematical approximation for illumination
        lux_avg =getSmooth(lux_f);
        
        Serial.print("LuxR: ");
        Serial.print(lichtRaw);
        Serial.println();
        Serial.print("LuxWert: ");
        Serial.print(lichtWert);
        Serial.println();
        Serial.print("Lux: ");
        Serial.print(lux_f,1);
        Serial.println();
        Serial.print("LuxAvg: ");
        Serial.print(lux_avg,0);
        Serial.println();
        Serial.println();
        delay(1000);
}*/