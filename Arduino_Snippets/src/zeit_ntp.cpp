#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <Benwifi.h>

Benwifi benwifi;

char* ssid = benwifi.ssid;                // Your "SSID"
char* passw = benwifi.passwort;             // Your "SUPER_SECRET_PASSWORD"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;


void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");
Serial.print("Month: ");
  Serial.println(&timeinfo, "%e");
  
  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.print("Uhrzeit: ");
  Serial.println(&timeinfo, "%R");
  Serial.print("KW: ");
  Serial.println(&timeinfo, "%V");
  Serial.print("Datum: ");
  Serial.println(&timeinfo, "%A, %d %B %Y");
  Serial.println();
  
}

void setup(){
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.println("Connecting to ");
  //Serial.println(ssid);
  //WiFi.mode(WIFI_STA);            // Set Wifi to connect a Station
  WiFi.begin(ssid, passw);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
 
  
}

void loop(){
  delay(1000);
  printLocalTime();
}*/