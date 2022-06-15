
//#define ESP01
#define ESP32

#ifdef ESP01
#include <ESP8266WiFi.h>
#endif  

#ifdef ESP32
#include <WiFi.h>
#endif

#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <Benwifi.h>



// Wire Pin Definitions /////
#define sdaPin  0   // GPIO 00 as SDA on I2C Bus
#define sclPin  2   // GPIO 02 as SCL on I2C Bus
#define dhtPin  3   // RX0  for GPIO 03

#define dhtType  DHT21    // DHT22 // Dht Sensor Typ (AM2301 = DHT21)

 /////////// WiFi stuff /////////////////////
 
WiFiClient espClient;                     ////// Instanzen von Objekt erstellen (Uebergabewert)
PubSubClient client(espClient);
Adafruit_BMP280 bmp; // I2C
DHT dht(dhtPin, dhtType);
Benwifi benwifi;

char* ssid = benwifi.ssid();                // Your "SSID"
char* passw = benwifi.passwort();             // Your "SUPER_SECRET_PASSWORD"
const char* mqtt = "XXXXXXXXX";                      //// MQTT Broker Hostname

/////////
//////////// Variablen fuer Messwerte initialisieren ///////////

float tempAvg, tempBmp, pressure, alti, tempDht, humi, altiForPress;

////////
/////////// Objekte ///////////


/////
//////////// MQTT Verbinden //////////

void reconnect() {
  
  // Loop until we're reconnected
  while (!client.connected()) {
    
    //Serial.print("Verbinde MQTT Broker...");
    // Create a client ID
    String clientId = "ESP01-Barometer";
    String nodeOn = " verbunden";
    clientId += nodeOn;
    
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      //Serial.println("verbunden");
      // Once connected, publish an announcement once...
      client.publish("iot/barometer/state", clientId.c_str(), false);
     
      } else {
      
        client.publish("iot/barometer/alarm", "MQTT KEINE VERBINDUNG , warte");
        delay(2000); // wait and try again
      }
    }
}

////////////


 
void setup() {
  
  //pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();      // Sensor Init
  Wire.begin(sdaPin,sclPin);    // Declare Pins for I2C Wire comunication
  bmp.begin();                  // Sensor Init Default 0x77, Alternative (0x76)
  bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X4,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_1); /* Standby time. */

  WiFi.mode(WIFI_STA);            // Set Wifi to connect a Station
  WiFi.hostname("Barometer");     // Set a Hostname for DHCP
  WiFi.begin(ssid, passw);     // Provide Wifi Credientials
  delay(1000);                    // wait for it
  client.setServer(mqtt, 1883);   // MQTT init with (Host, Port)
      
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if (!client.connected()) {           // if client is not connected , reconnect
    reconnect(); 
    
    }
    
  client.loop();   {        // MQTT Loop 

    
    /// BMP280 Sensor ///
    
    if (bmp.takeForcedMeasurement()) {    // Take a single Shot measurement with settings above from BMP280 Sensor
    
    delay(1000);    // wait for it to finish
    
       //  print out the new measurements
       
    float tempBmp = (bmp.readTemperature());    // Read the Value and save it in variable
    //char tempString[8];
        //dtostrf(tempBmp, 6, 1, tempString);
            //client.publish("iot/barometer/temp" , tempString, false);

    float pressure = (bmp.readPressure()/100);    // Read the Value and save it in variable
    char pressString[8];                          // creat a char array to hold a string 
        dtostrf(pressure, 6, 1, pressString);     // convert float, 6 digits, 1 komma, to newString type
            client.publish("iot/barometer/druck" , pressString, false);   // Publish MQTT Topic, MessageString, retain Flag
               
    float altiForPress = (bmp.seaLevelForAltitude(515.00f, pressure)); // Adjusted to local position! 
    char altiForPressString[8];
        dtostrf(altiForPress, 6, 1, altiForPressString);
            client.publish("iot/barometer/hoeheDruck" , altiForPressString, false);
    
    float alti = (bmp.readAltitude(altiForPress)); // Adjusted to local forecast! or value from sealevel
    char altiString[8];
        dtostrf(alti, 6, 1, altiString);
            client.publish("iot/barometer/hoehe" , altiString, false);

    delay(2000); 
    
      /// Values from DHT Sensor
      
    float tempDht = dht.readTemperature();
    
    
    float humi = dht.readHumidity();
    char humiString[8];
        dtostrf(humi, 6, 1, humiString);
            client.publish("iot/barometer/humi" , humiString, false);

     /// Temp average from both Sensors
    tempAvg = ((tempBmp + tempDht)/2);    // calculate temp average from both sensors
    char avgString[8];
        dtostrf(tempAvg, 6, 1, avgString);
            client.publish("iot/barometer/temp" , avgString, false); 
    delay(2000);
           
    } else {
    
        client.publish("iot/barometer/alarm" , "BMP Forced measurement failed!");
        delay(2000);
        }
    
    client.publish("iot/barometer/state", "Bis bald !");

    }
  
  client.disconnect();      // Disconnect from MQTT Beoker
  WiFi.disconnect();        // Disconnect from Router
  ESP.deepSleep(300e6);     // Set Sleep for some time in nano seconds (0 = sleep until pin 16 HIGH)
  
}