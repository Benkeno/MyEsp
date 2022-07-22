//////////////////////////////////////////////////////////////////////
////////////////// BIBLIOTHEKEN LADEN  ///////////////////////////////
//////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <DHT.h>
///////////////////////////////////////////////////////////////////////
//////////////   VARIABLEN DEKLARIEREN   //////////////////////////////
///////////////////////////////////////////////////////////////////////

const int TempPin = 4;          
const int FeuchtPin = A0;
const int PotiPin = A2;
const int LichtSensorPin = A3;    
const int Buzzer = 9;             
const int servo1Pin = 7;           
const int Button1Pin = 8;        
const int Button2Pin = 13;
//const int Button3Pin = 13;
const int RELAIS =  3;


float Temp = 0;                       // Temperaturwert 
float Humi = 0;                       // LuftFeuchte
int T_grenzwert = 15;                 // Schaltwert für Servobewegung Temp oder Feuchte in T_Grenzwert tauschen
const int T_warten = 30000;           // Wartezeit bis Bewegung
int TA_wert = 38;                     // Alarmwert für Temp oder Feuchte
const int TA_warten = 20000;          // Wartezeit bis zum Alarm
bool zuWarm = false;
bool lichtAn = false;
bool zuTrocken = false;
int winkel = 0;
int LichtWert = 0;
int FeuchtWert = 0;
int mapFeuchtWert = 90;
int button1State = HIGH;
int button2State = HIGH;

int lastButton1State;
int lastButton2State;

int taster1 = HIGH;
int taster2 = HIGH;

int mode_count = 1;
int potiWert = 0;
int RELAISState = HIGH;
//unsigned long einTag = 864e5;
//unsigned long eineStunde = 36e5;
//unsigned long eineMinute = 6e4;
//unsigned long std_18 = 64.8e6;
//unsigned long std_8 = 28.8e6;
unsigned long ON_timeLong = 10000;
unsigned long OFF_timeLong = 2000;
unsigned long ON_timeShort = 1000;    // gilt als OFFTIME
unsigned long OFF_timeShort = 5000;   // gilt als ONTIME bei short
unsigned long timestamp1 = 0;
unsigned long timestamp2 = 0;
unsigned long timestamp3 = 0;
unsigned long timestamp4 = 0;
unsigned long timestamp5 = 0;
unsigned long timestamp6 = 0;
unsigned long millis();
unsigned long lastDebounceTime;
const int debounceDelay = 20;

byte kreisle[8] = {  // Celsiuskringel

  0b01110,
  0b10001,
  0b01110,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
  };

#define DHTTYPE DHT22   // DHT 22  (AM2302)

///////////////////////////////////////////////////////////////////////
////////  OBJEKTE AUS BILBLIOTHEKEN INSTANZIEIEREN ////////////////////
///////////////////////////////////////////////////////////////////////

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo1;
DHT dht(TempPin, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

///////////////////////////////////////////////////////////////////////
///////////////////////  STARTBILDSCHRIM  /////////////////////////////
///////////////////////////////////////////////////////////////////////

void startMessage() {
  lcd.setCursor(0,0);
  lcd.print("Hallo Welt !!!!!");
  lcd.setCursor(0,1);
  lcd.print(" Glei gehts los ");
  delay(500);
  lcd.home();
  lcd.clear();
   
   
}

//////////////////////////////////////////////////////////////////////
///// TEMPERATUR UND FEUCHTE MESSEN, AUSGABE ALS STING ///
//////////////////////////////////////////////////////////////////////
void TempMessen() {

  if (millis() - timestamp1 > 2000) {   
    timestamp1 = millis();
  
    Humi = dht.readHumidity();
    Temp = dht.readTemperature();

}
}

/////////////////////////////////////////////////////
//////// TEMP2LCD  ///////////////////////////
/////////////////////////////////////////////////
void TempAnzeige() {

  char TempString[3];                            // initialize char array (8) index
      dtostrf(Temp, 3, 0, TempString);           // convert float to string for display (Float, digits, dezimals, FloatAsString)
        
  lcd.setCursor(0,0);
  lcd.print((String)"Tmp:" + TempString);
  //lcd.setCursor(8,0);
  //lcd.write(0);
}

/////////////////////////////////////////////////////
//////// HUMI2LCD  ///////////////////////////
/////////////////////////////////////////////////
void HumiAnzeige() {

  char HumiString[5];                            // initialize char array (8) index
      dtostrf(Humi, 5, 1, HumiString);           // convert float to string for display (Float, digits, dezimals, FloatAsString)
        
  lcd.setCursor(13,0);
  lcd.print(Humi,0);
  lcd.setCursor(15,0);
  lcd.print("%");
}
////////////////////////////////////////////////////////////////////
//////////////  SCHWELLENWERT FÜR AKTION SETZEN  ///////////////////
////////////////////////////////////////////////////////////////////
void Setze_T_Grenzwert() {
  
   potiWert = analogRead(PotiPin);                  // read the Pin save to variable
   
   T_grenzwert = map(potiWert,0,1023,10,42);        // map analog value to 0-42°
   
    char ThermoString[2];                           // initialize char array (8) index
      dtostrf(T_grenzwert, 2, 0, ThermoString);     // convert float to string for display (Float, digits, dezimals, FloatAsString)
  
  
    lcd.setCursor(7,0);
    lcd.print((String)"|" + ThermoString);
    lcd.setCursor(10,0);
    lcd.write(0);

}

/////////////////////////////////////////////////////////////////
/////////   SERVO BEWEGEN  / TÜR ÖFFNEN   ////////////////
////////////////////////////////////////////////////////////
void servoZu() {  


  if (winkel <= 0) {                              // check servo angle is smaller or equal 0
    
    for (winkel = 0; winkel <= 50; winkel++) {    // loop through as long angle is smaller or equal than 90
          
  
        servo1.write(winkel);                    // move servo 1° each loop
        delay(15);                               // with some delay (millis would be better) from another library
      }
    }
}
    
/////////////////////////////////////////////////////////////////
/////////  SERVO BEWEGEN  / TÜR SCHLIESSEN   ////////////////
////////////////////////////////////////////////////////////
void servoAuf() {
  
    if (winkel >= 50) {                             // check servo angle is greater or equal 90
    
      for (winkel = 50; winkel >= 0; winkel--) {    // loop through as long angle is greater or equal than 0
  
          servo1.write(winkel);                     // move servo 1° each loop
          delay(15);                                  // with some delay (millis would be better) from another library
        } 
      }
}

/////////////////////////////////////////////////////////////////////
// SERVOBEWEGUNG, VERZÖGERT UM (T_warten)  WENN T_grenzwert AUS Setze_T_Grenzwert ÜBERSCHRITTEN  ///
/////////////////////////////////////////////////////////////////////
void tempRegeln(int T_grenzwert, int T_warten) {
    
  if (millis() - timestamp5 >= T_warten) {            // has time gone
      timestamp5 = millis();                          // take new millis for next loop
      
      if (Temp >= T_grenzwert) {                // if Temp greater than Set
            servoAuf();                               // execute open funktion
        }
        else {
          servoZu();                                  // execute close funktion
          }
    }
    
}

 
/////////////////////////////////////////////////////////////////////
/////  VERZÖGERTER ALARM WENN MESSWERT AUSSERHALB GESETZTEM WERT  ///
/////////////////////////////////////////////////////////////////////
void T_alarm(int TA_wert, int TA_warten) {  
  
   if (millis() - timestamp3 >= TA_warten) {      // has time gone
      timestamp3 = millis();                      // take new millis for next loop
      if (Temp <= TA_wert) {                // if Temp greater than Set
     
         zuWarm = false;                          // set bool to false
          
          } else {                                  // else
            
            zuWarm = true;                          // set bool to false
            }
      }   
    
   if ((zuWarm) || (mapFeuchtWert < 20)) {                                    // than check if zuWarm = true
      
        piepen();                                   // make beep sequenz
        
      } else  {
    
          ruhe();                                   // make no beep sound
          
         }
}

/////////////////////////////////////////////////////////////////////
///////////  PIEPSOUND  JEDE SEKUNDE FÜR 1/10 sec ///////////////////
/////////////////////////////////////////////////////////////////////
void piepen(){
  
tone(Buzzer,440, millis() % (1000 + 100) >= 100);       // Beeps every second for 10th second
  
}
 
/////////////////////////////////////////////////////////////////////
/////////////////////  PIEPSER AUSSCHALTEN  /////////////////////////
/////////////////////////////////////////////////////////////////////
void ruhe() {
  noTone(Buzzer);                                     // this is nosound
}

/////////////////////////////////////////////////////////////////////
////////////////  LICHT MESSEN  /////////////////////////////////////
/////////////////////////////////////////////////////////////////////
void lichtMessen() {

  RELAISState = digitalRead(RELAIS);

  LichtWert = analogRead(LichtSensorPin);
  
  if ( RELAISState == HIGH){
      lcd.setCursor(0,1);
      lcd.print("LICHT AUS ");
      
    } 
  
  if ( RELAISState == LOW){
      lcd.setCursor(0,1);
      lcd.print("LICHT AN  ");
      
      }
   
}

/////////////////////////////////////////////////////////////////////
/////////////  LICHT MIT BUTTON2 SCHALTEN  /////////////////////////////////////
/////////////////////////////////////////////////////////////////////
void manuellSchalten() {

  int taster2 =   digitalRead(Button2Pin); 

  
  if (millis() - lastDebounceTime > debounceDelay) {
     lastDebounceTime = millis();
    if (taster2 != button2State) {
      button2State = taster2;
     
      
      if (taster2 == LOW) {
        RELAISState = !RELAISState;
        }
      }
    }
digitalWrite(RELAIS,RELAISState);
  
}
   
/////////////////////////////////////////////////////////////////////
/////////////  LICHTAUTOMATIK  18H/6H ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////
void lichtAuto18(long OFF_timeLong, long ON_timeLong) {

// Toggle State every On_Time for some Off-Time hours
// Set for 24h days. 
 digitalWrite(RELAIS, millis() % (OFF_timeLong + ON_timeLong) >= ON_timeLong);
}   


/////////////////////////////////////////////////////////////////////
/////////////  LICHTAUTOMATIK  8H/16H ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////
void lichtAuto08(long OFF_timeShort, long ON_timeShort) {
  
// Toggle State every On_Time for some Off-Time hours
// Set for 24h days. 
unsigned long millis();
digitalWrite(RELAIS, millis() % (OFF_timeShort + ON_timeShort) >= OFF_timeShort);
  }
    
 


void WasserMessen() {
  
if (millis() - timestamp6 > 18e5) {
     timestamp6 = millis();{
  
 
 FeuchtWert = analogRead(A0);

 mapFeuchtWert = map(FeuchtWert,0,1023, 10,99);
     }
     }
}

void WasserAnzeige() {   
   
       
  lcd.setCursor(12,0);
  lcd.print(mapFeuchtWert);
  //lcd.print(mapFeuchtWert);
  //lcd.setCursor(15,0);
  //lcd.print("%");
  
}
/////////////////////////////////////////////////////////////////////
/////////////  INITIAL SETUP  ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void setup() {
  digitalWrite(RELAIS, HIGH);
  Serial.begin(9600);
  dht.begin();
  pinMode(Button1Pin, INPUT_PULLUP);
  pinMode(Button2Pin, INPUT_PULLUP);
  //pinMode(Button3Pin, INPUT_PULLUP);
  pinMode(TempPin, INPUT);
  pinMode(LichtSensorPin, INPUT);
  pinMode(PotiPin, INPUT);
  pinMode(FeuchtPin, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(RELAIS, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, kreisle); 
  lcd.home();
  startMessage();
  servo1.attach(servo1Pin);
  servo1.write(0);
  
  
}

////////////////////////////////////////////////////////////////////
////////////   ENDLOS LOOP   ///////////////////////////////////////
//////////////////////////////////////////////////////////////////// 

void loop() {

  //Serial.println(mapFeuchtWert);
TempMessen();
  WasserMessen();
  lichtMessen();

  int taster1 =  digitalRead(Button1Pin);                 // read the PinStaus HIGH or LOW
  
    if ((millis() - lastDebounceTime) > debounceDelay) {  // check if some ms have gone
    
      if (taster1 != button1State) {                      // if button state is different
          button1State = taster1;                                     // take new State for next loop
          lastDebounceTime = millis();                                          // reset the timer
      
          if (taster1 == LOW){                        //When button is pressed (LOW state)
              lcd.clear();                             // eq lcd.clear //When page is changed, lcd clear to print new page

              if(mode_count <4){                          //Page counter never higher than 4(total of pages)
                mode_count= mode_count +1;                //Page up

              } else {                              // If page higher than 4 , stay back to page 1
                  mode_count= 1;
                  }
              }
          } 
      }
        
   switch (mode_count) {
      case 1:{                                  //Design and funktions of home page 1
          //lcd.setCursor(0,1); 
          //lcd.print("  Licht Manuell ");
          //TempMessen();
          T_alarm(TA_wert,TA_warten);
          Setze_T_Grenzwert();
          tempRegeln(T_grenzwert, T_warten);
          
          manuellSchalten();
          lcd.setCursor(10,1);
          lcd.print("T-:---");
          TempAnzeige();
          HumiAnzeige();
          
          
        }
      break;
      
        case 2: {                               //Design of page 2
          //lcd.setCursor(0,1); 
          //lcd.print("  Licht 18h AN ");
          manuellSchalten();
          lcd.setCursor(10,1);
          lcd.print("T-:---");
          //TempMessen();
          
          TempAnzeige();
          
          WasserAnzeige(); 
          T_alarm(TA_wert,TA_warten); 
          Setze_T_Grenzwert();
          tempRegeln(T_grenzwert, T_warten);
        } 
      break;
      
      case 3: {                                 //Design of page 3
          //lcd.setCursor(0,1); 
          //lcd.print("  Licht 8h AN  ");
          lichtAuto08(OFF_timeShort, ON_timeShort);
          lcd.setCursor(10,1);
          lcd.print("T-: 8h");
          //TempMessen(); 
          TempAnzeige();
          HumiAnzeige();
          T_alarm(TA_wert,TA_warten);
          Setze_T_Grenzwert();
          tempRegeln(T_grenzwert, T_warten);
       
        }
      break;

      case 4: {                                 //Design of page 4
          //lcd.setCursor(0,1); 
          //lcd.print("  Licht 18h AN ");
          lichtAuto18(OFF_timeLong, ON_timeLong);
          lcd.setCursor(10,1);
          lcd.print("T-:18h");
          //TempMessen();
          TempAnzeige();
          HumiAnzeige(); 
          T_alarm(TA_wert,TA_warten); 
          Setze_T_Grenzwert();
          tempRegeln(T_grenzwert, T_warten);
        
        } 
      break;

      


  }     //switch ende


}
