#include <Arduino.h>
#include <Adafruit_INA219.h>
/////////////////////////////////////////////////////////////////////////////////////////
///// DEFINE ALIAS NAMES for values

#define BATTERYSENSOR_PIN 26                    // Pin for Voltage Sensor
#define BATTERYSENSOR_VOLTAGE 3.33f             // RefVoltage ADC (ESP32 ADC 4095 = 3,3V)
//////////////////////////////////////////////////////////////////////////////////////////
///// Create Instance of INA210 Sensor  //////////

Adafruit_INA219 ina219(0x40);

////////////////////////////////////////////////////////////////////////////////////////
/////   Constant VoltageSensor Variables  as float f ////////
const float R1 = 30200.0f;                      // Resistor OHM R1 on Sensor Module
const float R2 = 7500.0f;                       // Resistor OHM R2 on Sensor Module
const float B_Vref = BATTERYSENSOR_VOLTAGE;     // Panel Senor to P_Vref
//////////////////////////////////////////////////////////////////////////////////////////
///// Initialize Energy Sensor INA219 Variables Float f for comma numbers       ////////////

float shuntvoltage = 0.0f;
float busvoltage = 0.0f;
float current_mA = 0.0f;
float loadVoltage = 0.0f;
float wattActual = 0.0f;

/////////////////////////////////////////////////////////////////////////////////////////
////    BATTERY VOLTAGE  MAX.25V VOTLAGE DIVIDER ///////////
const int numOfReadings = 100;
float readings[numOfReadings];
int readIndex = 0;
float total = 0.0f;
float average = 0.0f;

void batteryVoltage() {


static unsigned long adcBatterySampleTimepoint = millis();              // stets a timepiont from timer instance of actual millisec
static unsigned long adcBatteryPrintTimepoint = millis();


  if (millis() - adcBatterySampleTimepoint > 10U) {                    // if running time - timepoint time > 500 millis
  

    adcBatterySampleTimepoint = millis();                               // set an actual timepiont for the next run

    
    
    float adcValue = analogRead(BATTERYSENSOR_PIN) * B_Vref /4095.0f;   // calculate sensorreading to the Voltage 0V = 0 - 3.3V = 4096 (12bit ADC)
    float battery_Vout = adcValue / (R2/(R1+R2));                       // Ohms law !  U / R  to get 0-24V
    
      
        total = total - readings[readIndex];                                    // subtract the last reading
        readings[readIndex] = battery_Vout;                                     // read the value for sensor
        total = total + readings[readIndex];                                    // add reading to array with indexposition
        readIndex = readIndex + 1;                                              // advance to next postion of array
          if (readIndex >= numOfReadings) {                                     // if array ends
            readIndex = 0;                                                        // set Index no. to 0
            }
        
      }
    average = total / numOfReadings;                                            // after all calculate the average

      if (millis() - adcBatteryPrintTimepoint > 1000U) {
        adcBatteryPrintTimepoint = millis(); 
        Serial.print("Akku Spannung:   ");                                // Text to display
        Serial.print(average,2);                                       // Text the variable name wich contains the calculated float value, 2 dezimal
        Serial.println(" V");
      }
  }



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
////    PANEL ENERGY  INA-219 SENSOR //////////////
void panel_energy() {

  static unsigned long adcPanelSampleTimepoint = millis();              // stets a timepiont from timer instance of actual millisec


  if (millis() - adcPanelSampleTimepoint > 1000U) {                      // if running time - timepoint time > 500 millis

    adcPanelSampleTimepoint = millis();                                 // set an actual timepiont for the next run


    shuntvoltage = ina219.getShuntVoltage_mV();                         // variable from ina219 function 
    busvoltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    loadVoltage = busvoltage + (shuntvoltage / 1000.00f) + 0.15f;
    wattActual = loadVoltage * (current_mA / 1000.00f);

    //Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
    //Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
    Serial.print("Panel Spannung:  "); Serial.print(loadVoltage); Serial.println(" V");
    Serial.print("Panel Strom:     "); Serial.print(current_mA); Serial.println(" mA");
    Serial.print("Watt/h:          "); Serial.print(wattActual); Serial.println(" W/h");
    Serial.println("");
  }
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//// SETUP RUNNING ONCE   ////////

void setup() {
  
  Serial.begin(115200);                                             // Begin Serial Communication for Debugging and Output to Terminal
  pinMode(BATTERYSENSOR_PIN, INPUT);                                // setup the Pin as input
  ina219.begin();                                                   // start the instance for energy sensor ina219
  //for (int thisReading = 0; thisReading < numOfReadings; thisReading++) {   // count up the reading counter
    //readings[thisReading] = 0;
  //}
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////  LOOP FOREVER  /////////

void loop() {                                                       

  batteryVoltage();      
  panel_energy();    
}
