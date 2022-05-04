#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

#define DHTPIN  4           // DHT22 data pin is connected to Arduino analog pin 
#define DHTTYPE AM2301




unsigned long interval = 20000;
int timepoint = 0;

Adafruit_BMP280 bmp; // I2C Create Instanz from Objekt
DHT dht22(DHTPIN, DHTTYPE);



void readDHT() {     

    float t = dht22.readTemperature();
    float h = dht22.readHumidity();
        
        if ((t > -30) && (t < 65)) { 
            // Convert the value to a char array
                //char tempString[8];
                //dtostrf(t, 6, 1, tempString);
                Serial.print(F("Temperatur_Dht: "));
                Serial.print(t);
                Serial.println(" *C");
            }

            if ((h > 10) && (h < 100)) { 
            // Convert the value to a char array
                //char humString[8];
                //dtostrf(h, 6, 1, humString);
                Serial.print(F("Luft Rel.: "));
                Serial.print(h);
                Serial.println("%");
            }
        

}

void readBmp() {       

    if (bmp.takeForcedMeasurement()) {
    // can now print out the new measurements
    Serial.print(F("Temperatur: "));
    Serial.print(bmp.readTemperature ());
    Serial.println(" °C");

    Serial.print(F("Luftdruck: "));
    Serial.print(bmp.readPressure()/100);
    Serial.println(" hPa");

    Serial.print(F("Höhe üN: "));
    Serial.print(bmp.readAltitude(1017)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    
    } else {
        Serial.println("Messung Fehlgeschlagen, Senosor prüfen !");
        }
          
        
}


void setup() {

  Serial.begin(115200);
  dht22.begin();
  bmp.begin();
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_1); /* Standby time. */
}

void loop() {

unsigned long millis();
    if (millis() - timepoint > interval) {
        timepoint = millis();
        //readDHT();
        readBmp();
    }
 
}