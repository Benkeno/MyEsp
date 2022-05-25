/*#include <Arduino.h>
// Formula: lux = LUXFACTOR * pow(EULERNUMBER, (lichtWertFACTOR * digitallichtWert))
#define EULERNUMBER 2.718281828459
int grueneLED =  12;   //Pin der grünen LED
int gelbeLED =  13; //Pin der gelben LED
int roteLED =  14; //Pin der roten LED
int licht = 4;
int lichtWert = 0;
double lux_f = 0;
int timestamp = 0;
int hell = 0;
int dimmer = +5;
int pieper = 5;

String gelesen = "";    // String steht für Text

void setup()
{
  pinMode(grueneLED,OUTPUT);                         //gruene LED als OUTPUT
  pinMode(gelbeLED, OUTPUT);                        //gelbe LED als OUTPUT
  pinMode(roteLED, OUTPUT);
  pinMode(pieper, OUTPUT) ;                        //rote LED als OUTPUT
  pinMode(licht, INPUT);
  //ledcAttachPin(pieper,0);
  ledcSetup(4,5000,8);
  Serial.begin(115200);                               //Start Kommunikation
  Serial.print("Bitte gewünsche Farbe eingeben");   //Ausgabe von der Frage
  Serial.println();


}
/*
double getLux (int lichtWert)
{
  double Vout=lichtWert*0.0048828125;
  int lux=500/(10*((5-Vout)/Vout));//use this equation if the LDR is in the upper part of the divider
  //int lux=(2500/Vout-500)/10;
  return lux;
}*/
/*
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
void loop()
{//-----------------------------------------------------------------
// Auslesen der Eingabe
//-----------------------------------------------------------------
  if(Serial.available()>0) {             // Wenn wir eine gültige Einghabe erhalten haben
    gelesen = "";                       // Am Anfang noch nichts gelesen
    gelesen = Serial.readStringUntil('\n');   // Buchstabe nach und nach hinzufügenb
    delay(2);
    Serial.println(gelesen);                     // Nochmals ausgelesendes drucken
  }
//-----------------------------------------------------------------
// AB HIER ABFRAGE DES GELESENEN
//-----------------------------------------------------------------
    if(gelesen == "rot")
    {
      digitalWrite(roteLED, HIGH);//turn the red led on
      digitalWrite(grueneLED, LOW);//turn the green led off
      digitalWrite(gelbeLED, LOW);//turn the yellow led off
    }
    else if(gelesen == "gelb")
    {
      digitalWrite(roteLED, LOW);//turn the red led off
      digitalWrite(grueneLED, LOW);//turn the green led off
      digitalWrite(gelbeLED, HIGH);//turn the yellow led on
    }
    else if(gelesen == "gruen")
    {
      digitalWrite(roteLED, LOW);//turn the red led off
      digitalWrite(grueneLED, HIGH);//turn the green led on
      digitalWrite(gelbeLED, LOW);//turn the yellow led off
    }

    else if (gelesen == "dim")
    {
        if ((millis() - timestamp) > 5) {
        timestamp = millis();
        analogWrite(roteLED,  hell);
        analogWrite(gelbeLED,  hell);
        analogWrite(grueneLED, hell);
        hell = hell + dimmer;
        
        if (hell <= 0 || hell >= 255) {
        dimmer = -dimmer; 
        } 
      } 
    }
    else if (gelesen == "blink") {

        digitalWrite(grueneLED, !(millis() % 1000 >= 500));
        digitalWrite(roteLED, millis() % 1000 >= 500);
        

    }
    
    else if (gelesen == "play1") {
        ledcAttachPin(pieper, 4);
        ledcWriteTone(4, 1046);
        delay(150);
        ledcWriteTone(4, 1318);
        delay(150);
        ledcWriteTone(4, 1567);
        delay(150);
        ledcWriteTone(4, 2093);
        delay(150);
        ledcWriteTone(4, 2637);
        delay(150);
        ledcWriteTone(4, 3135);
        delay(400);
        
        ledcWriteTone(4, 2637);
        delay(400);
        ledcWriteTone(4, 1046);
        delay(150);
        ledcWriteTone(4, 1244);
        delay(150);
        ledcWriteTone(4, 1661);
        delay(150);
        ledcWriteTone(4, 2093);
        delay(150);
        ledcWriteTone(4, 2489);
        delay(150);
        ledcWriteTone(4, 3322);
        delay(400);
        ledcWriteTone(4, 2489);
        delay(400);
        ledcWriteTone(4, 1174);
        delay(150);
        ledcWriteTone(4, 1396);
        delay(150);
        ledcWriteTone(4, 932);
        delay(150);
        ledcWriteTone(4, 2349);
        delay(150);
        ledcWriteTone(4, 2793);
        delay(150);
        ledcWriteTone(4, 1864);
        delay(150);
        ledcWriteTone(4, 0);
        delay(400);
        ledcWriteTone(4, 1864);
        delay(120);
        ledcWriteTone(4, 0);
        delay(60);
        ledcWriteTone(4, 1864);
        delay(120);
        ledcWriteTone(4, 0);
        delay(60);
        ledcWriteTone(4, 1864);
        delay(120);
        ledcWriteTone(4, 0);
        delay(60);
        ledcWriteTone(4, 4186);
        delay(900);
        ledcWriteTone(4, 0);
        delay(2000);
    }

else if (gelesen == "licht") {

        int lichtRaw = analogRead(licht);
        int lichtWert  = map(lichtRaw, 0,4095,0,1023);
   
        lux_f = getLux(lichtWert);      // Use mathematical approximation for illumination
        Serial.print("Lux: ");
        Serial.print(lux_f,1);
        Serial.println();
        Serial.print("LuxR: ");
        Serial.print(lichtRaw);
        Serial.println();
        Serial.print("LuxWert: ");
        Serial.print(lichtWert);
        Serial.println();
        Serial.println();
        delay(1000);
}
    else
    {
      digitalWrite(roteLED, LOW);//turn the red led off
      digitalWrite(grueneLED, LOW);//turn the green led off
      digitalWrite(gelbeLED, LOW);//turn the yellow led off
    }    
}
*/