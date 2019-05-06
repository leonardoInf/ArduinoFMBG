// *** Abhängigkeiten     ****
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>        //
#include <BigNumber.h>    
#include <HCSR04.h>       //Entfernung (Ultraschall)
#include <SFE_BMP180.h>   //Luftdruck

#ifndef I2CLCD
#include <LiquidCrystal.h>
#endif

#ifdef ERWEITERT
#include <Wire.h>
#endif

#ifdef I2CLCD
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#endif

//Eigene Dateien
#include "globals.h"  //KONFIGURATIONEN befinden sich hier
#include "Sensoren.h"
#include "read.h"
// ***

// ***                    ****

#if defined(I2CLCD) && defined(ERWEITERT)
#error "I2C-Erweiterungen mit gleichzeitiger Verwendung von I2C-LCD werden zurzeit nicht unterstützt"
#endif

#if defined(WLAN) && defined(SERIELLE_AUSGABE)
#error "Serielle Ausgabe kollidiert normalerweise mit Kommunikation zum ESP8266, 'z' vor alle Zeichenketten setzen, um dies zu verhindern"
#endif

#if defined(WLAN) && defined(UNO)
#error "Arduino Uno ist hier mit ESP8266 nicht kompatibel"
#endif

#if !defined(I2CLCD) && defined(UNO)
#error "Arduino Uno sollte mit I2CLCD verwendet werden"
#endif

// *** Konstanten und Variablen für die h-Bestimmmung  ***
const BigNumber p_max PROGMEM = 5;  // 5 W/m^2
const BigNumber zero PROGMEM = 0;
const BigNumber eins PROGMEM = 1;
const BigNumber vier PROGMEM = 4;
const BigNumber zehn PROGMEM = 10;
const BigNumber neunzehn PROGMEM = 19;
const BigNumber vierunddreissig PROGMEM = 34;
const BigNumber hundert PROGMEM = 100;
const BigNumber materialien[][7] PROGMEM = {
      {1.8, 1.94, 2.25, 2.28, 4.2, 4.27, 4.48}, 
      {0.17, 0.29, 0.18, 0.28, 0.30, 0.21, 0.23},
};
const char* symbole[] {
      "Ba", "Cs", "K", "Na", "Al", "Zn", "Cu"
  };
 const BigNumber minus_eins;
  const BigNumber l_inc;
  const BigNumber l_min;
  const BigNumber l_max;
  const BigNumber h;
  const BigNumber c;
  const BigNumber elementarladung;
  const BigNumber nano;
  int m_index = 0;
  BigNumber ausloesearbeit;
  BigNumber ausbeute;
  BigNumber wellenlaenge;
//***                                      ****

// *** Globale Variablen (siehe globals.h) ****
boolean isactive = false;
boolean tabelle = false;
boolean MessungDurchfuehren = false;
int tolPercent = 5;
int stufeK = 0;
int backK = 0;
int sIndex = 0;
int sIndex2 = 0;
int posK = 0;
boolean allowInput = true;
int index = 0;
// ***                                    ****

// *** Variablen für menue.ino            ****
boolean rcvMode = false;
#ifndef I2CLCD                    
enum{rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7};
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#else
Adafruit_SSD1306 lcd = Adafruit_SSD1306(128, 32, &Wire);
#endif

#if defined(WLAN) && !defined(UNO)
const char *optionen[] PROGMEM=  {"1. Temperatur/;Luftfeuchtigkeit",
                     "2. Hallsensor",
                     "3. h-Bestimmung;Simulation",
                     "4. Pendel",
                     "5. Schall",
                     "6. Luftdruck",
                     "7. Spannungs-;teiler",
                     "8. Kondensator",
                     "9. Wetter"
                    };
     const int anzahlOptionen = 9;
void lokalAusfuehren(char screen[]){
  switch(index){
    case 0:
      screen = temperatur(); break;
    case 1:
      screen = hallsensor(); break;
    case 2:
      screen = h_bestimmung(); break;
    case 3:
      screen = pendel(); break;
    case 4:
      screen = schall(); break;
    case 5:
      screen = luftdruck(); break;
    case 6:
      screen = spannungsteiler(); break;
    case 7:
      screen = kondensator(); break;
    case 8:
      screen = wetter(); break;
    default:
    ;  
  }    
}
#endif

#if !defined(WLAN) && !defined(UNO)
char *optionen[] =  {"1. Temperatur/;Luftfeuchtigkeit",
                     "2. Hallsensor",
                     "3. h-Bestimmung;Simulation",
                     "4. Pendel",
                     "5. Schall",
                     "6. Luftdruck",
                     "7. Spannungs-;teiler",
                     "8. Kondensator",
                    };
                    const int anzahlOptionen = 8;
  #ifdef I2CLCD
    optionen[6] = "8- Spannungsteiler";
  #endif
void lokalAusfuehren(char screen[]){
  switch(index){
    case 0:
      screen = temperatur(); break;
    case 1:
      screen = hallsensor(); break;
    case 2:
      screen = h_bestimmung(); break;
    case 3:
      screen = pendel(); break;
    case 4:
      screen = schall(); break;
    case 5:
      screen = luftdruck(); break;
    case 6:
      screen = spannungsteiler(); break;
    case 7:
      screen = kondensator(); break;
    default:
    ;  
  }    
}
#endif

#ifdef UNO
char *optionen[] =  {"1. Temperatur/;Luftfeuchtigkeit",
                     "2. Luftdruck",
                     "3. Fadenpendel",
                     "4. Schall",
                     "5. Spannungsteiler"
                    };
      const int anzahlOptionen = 5;
void lokalAusfuehren(char screen[]){
  switch(index){
    case 0:
      screen = temperatur(); break;
    case 1:
      screen = luftdruck(); break;
    case 2:
      screen = fadenpendel(); break;
    case 3:
      screen = schall(); break;
    default:
    ;  
  }    
}
#endif
