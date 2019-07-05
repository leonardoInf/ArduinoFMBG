#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
String urlbase = "http://192.168.1.15/t.php";
char zeichen = 'x';

void setup() {

  Serial.begin(9600);

  for (uint8_t t = 2; t > 0; t--) {
    //Serial.printf("[SETUP] WAIT %d...\n", t);
    //Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("o2-WLAN86", "6264263310767187");

}
void loop() {
  if(Serial.available() > 0){
      char c = Serial.read();
      if(c != 'z'){
      zeichen = c;
      }
      
      while(Serial.available() > 0)
        Serial.read();//sonstige 'verpasste' Zeichen löschen
  }

  
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    String url = urlZusammenstellen();

    if(zeichen == 'w' || zeichen == 's'){
    if (http.begin(client, url)) {
      int httpCode = http.GET();

      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
           String k = http.getString();
           if(zeichen == 'w' || zeichen == 's'){
              Serial.print(extrahieren(k));
              zeichen = 'x';
              }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
}
  delay(100);
}

String extrahieren(String s){
      s = s.substring(s.indexOf('|')+1);
      if(s.charAt(0) == '+')
        s = s.charAt(1);
      return s;
  }

String urlZusammenstellen(){
    if(zeichen == 'w'){
      return urlbase + "?cmd=wetter";
      }
    if(zeichen == 's'){
       return urlbase + "?cmd=steuerung";
      }
    return urlbase; 
}
#else
void setup(){}
void loop(){}
#endif
