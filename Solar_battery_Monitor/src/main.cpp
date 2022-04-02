#include <Arduino.h>
#include <Wire.h>
#include <INA219_WE.h>
#include <U8g2lib.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Create Instance of INA219 Sensor  as INA219solar (I2C-Adress) for measuring Values on Solarpanelside //////////
#define I2C_ADDRESS_SOLAR 0x41

INA219_WE ina219solar = INA219_WE(I2C_ADDRESS_SOLAR);

///// Create Instance of INA219 Sensor  as INA219solar (I2C-Adress) for measuring Values on Solarpanelside //////////
#define I2C_ADDRESS_BATTERIE 0x40

INA219_WE ina219bat = INA219_WE(I2C_ADDRESS_BATTERIE);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create Instance of SSD1306 Display as display  //////////////////////////////////////////////////////////////////

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   No.1 INA-219 SOLARPANEL SENSOR ////////////////////////

void panel_energy() {

float solar_shuntVoltage = 0.0f;
float solar_busVoltage = 0.0f;
float solar_current_mA = 0.0f;
float solar_loadVoltage = 0.0f;
float solar_power_mW = 0.0f;
bool solar_ina219_overflow = false;


    solar_shuntVoltage = ina219solar.getShuntVoltage_mV();
    solar_busVoltage = ina219solar.getBusVoltage_V();
    solar_current_mA = ina219solar.getCurrent_mA();
    solar_power_mW = ina219solar.getBusPower();
    solar_loadVoltage  = solar_busVoltage + (solar_shuntVoltage/1000);
    solar_ina219_overflow = ina219solar.getOverflow();


    //u8g2.clearBuffer();
    u8g2.setFontMode(0);
    u8g2.setFont(u8g2_font_squeezed_b6_tr);
    u8g2.drawStr(36,6,"Solarstrom");
    u8g2.drawHLine(0,8,127);

    u8g2.setFont(u8g2_font_bytesize_tr);
    u8g2.drawStr(2,27,"Volt   :");
    u8g2.setCursor(65,27);
    u8g2.print(solar_loadVoltage);

    u8g2.drawStr(2,45,"Amps :");
    u8g2.setCursor(65,45);
    u8g2.print((solar_current_mA) /1000);

    u8g2.drawStr(2,63,"Watt  :");
    u8g2.setCursor(65,63);
    u8g2.print((solar_power_mW) /1000);

    u8g2.sendBuffer();


    Serial.println("");
    Serial.println("SOLAR");
    Serial.print("Shunt Voltage [mV]: "); Serial.println(solar_shuntVoltage);
    Serial.print("Bus Voltage [V]: "); Serial.println(solar_busVoltage);
    Serial.print("Load Voltage [V]: "); Serial.println(solar_loadVoltage);
    Serial.print("Current [mA]: "); Serial.println(solar_current_mA);
    Serial.print("Bus Power [mW]: "); Serial.println(solar_power_mW);
    if(!solar_ina219_overflow){
      Serial.println("Solar Values OK - no overflow");
    }
    else{
      Serial.println("Solar Overflow! Choose higher PGAIN");
    }
    Serial.println();
  }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////     INA-219 BATTERIE SENSOR ( 75mV/40A shunt / 1000 = 0,001875 ohm ////////////////////////

void batterie_energy() {

float bat_shuntVoltage = 0.0f;
float bat_busVoltage = 0.0f;
float bat_current_mA = 0.0f;
float bat_loadVoltage = 0.0f;
float bat_power_mW = 0.0f;
bool bat_ina219_overflow = false;



    bat_shuntVoltage = ina219bat.getShuntVoltage_mV();
    bat_busVoltage = ina219bat.getBusVoltage_V();
    bat_current_mA = ina219bat.getCurrent_mA();
    bat_power_mW = ina219bat.getBusPower();
    bat_loadVoltage  = bat_busVoltage + (bat_shuntVoltage/1000);
    bat_ina219_overflow = ina219bat.getOverflow();
/*
    //u8g2.clearBuffer();
    //u8g2.drawBox(10,40,80,10);
    //u8g2.drawHLine(0,22,127);
    u8g2.drawStr(5,35,"Akku:");
    //u8g2.drawHLine(0,37,127);
    u8g2.setCursor(65,35);
    u8g2.print(bat_loadVoltage);
    //u8g2.drawBox(10,40,80,10);
    u8g2.sendBuffer();
*/   

    Serial.println("");
    Serial.println("BATTERIE");
    Serial.print("Shunt Voltage [mV]: "); Serial.println(bat_shuntVoltage);
    Serial.print("Bus Voltage [V]: "); Serial.println(bat_busVoltage);
    Serial.print("Load Voltage [V]: "); Serial.println(bat_loadVoltage);
    Serial.print("Current [mA]: "); Serial.println(bat_current_mA);
    Serial.print("Bus Power [mW]: "); Serial.println(bat_power_mW);

    if(!bat_ina219_overflow){
      Serial.println("Batterie Values OK - no overflow");
    }
    else{
      Serial.println("Batterie Overflow! Choose higher PGAIN");
    }
    Serial.println();
  }


//////////////////////////////////////////////////////////////////////////////////////////////////////
////// Welcome on startup 0.96" OLED I2C Display ///////////////////////////////


void welcome_message() {

  
    u8g2.clearBuffer();
    u8g2.setFontMode(0);
    u8g2.setFont(u8g2_font_moosenooks_tr);
    u8g2.setCursor(25, 35);
    u8g2.print(F("Whuuuu..."));
    //u8g2.drawStr(0,20,"Starte...");
    u8g2.sendBuffer();
  }


void solarsensor_init() {

  if(!ina219solar.init()){
    Serial.println("INA219solar not connected!");
    }                                                    // start the instance for energy sensor ina219
  ina219solar.setShuntSizeInOhms(0.01);                   // Shunt 320mV/3.2A = in Ohms (R100) /1000 /10= 0.01
  ina219solar.setADCMode(SAMPLE_MODE_128);               // set sample mode to mean value of 128 samples
  ina219solar.setPGain(PG_320);                           // Gain 80 for max 80 mV at shunt
  ina219solar.setCorrectionFactor(0.92);
  //ina219solar.setShuntVoltOffset_mV(0.30);
}

void batteriesensor_init() {

  if(!ina219bat.init()){
    Serial.println("INA219bat not connected!");
    }                                                           // start the instance for energy sensor ina219
  ina219bat.setShuntSizeInOhms(0.0001875);                       // Shunt 75mV/40A = in Ohms (R1.875) /1000 /10 = 0.0001875
  ina219bat.setADCMode(SAMPLE_MODE_128);                        // set sample mode to mean value of 128 samples
  ina219bat.setPGain(PG_80);                                    // Gain 80 for max 80 mV at shunt
  //ina219bat.setCorrectionFactor(0.92);
  //ina219solar.setShuntVoltOffset_mV(0.5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// SETUP RUNNING ONCE   ///////


void setup() {
  
  Serial.begin(115200);                    // Begin Serial Communication for Debugging and Output to Terminal
  
  u8g2.begin();                             // Start Display
  welcome_message();                        // Show message once
  delay(2000);                              // take a break
  Wire.begin();                             // Begin Wire Objekt communication I2C
  solarsensor_init();                       // Set solarsensor config
  batteriesensor_init();                    // Set batSensor config 
  
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////  LOOP FOREVER  /////////


void loop() {

  static unsigned long adcUpdateTimepoint = millis();                // stets a timepiont from timer instance of actual millisec

  if (millis() - adcUpdateTimepoint > 2000U) {                       // if running time - timepoint time > 2000 millis. Every 2 seconds...

    adcUpdateTimepoint = millis();                                    // set new updateTimePiont from actual millis for next run

    u8g2.clearBuffer();                                               // clear display buffer for following functions
    panel_energy();
    batterie_energy();
  
  }
} 
  

