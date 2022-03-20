#include <Arduino.h>
#include <WiFi.h>
 
 
const char *soft_ap_ssid = "MeinESP_AP";
const char *soft_ap_password = "supergeheim";
 
void OnWiFiEvent(WiFiEvent_t event)
{
  switch (event) {
 
    case SYSTEM_EVENT_AP_START:
      Serial.println("Wlan Accesspoint gestartet");
      break;
    case SYSTEM_EVENT_AP_STACONNECTED:
      Serial.println("Client connected");
      break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
      Serial.println("UHH.. Client DISSCONNECED");
      break;
    default: break;
  }
}
 
 
void setup() {
 
  Serial.begin(115200);
  WiFi.onEvent(OnWiFiEvent);
 
  WiFi.mode(WIFI_MODE_APSTA);
 
  WiFi.softAP(soft_ap_ssid, soft_ap_password);

}
 
void loop() {}