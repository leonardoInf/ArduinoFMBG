/*
   Globale Variablen für die Arduino-Messbox
   Leonardo Braguinski, 5. PK Physik/Informatik
*/

// ***  zusätzliche Optionen   ****
//#define ERWEITERT
#if defined(__AVR_ATmega328P__)
#define I2CLCD
#define UNO
#endif
//#define WLAN
//#define SERIELLE_AUSGABE
//#define VIER_TASTEN_MATRIX
// ***                         ****

// *** Pins                   ****
#define DIGITAL1 51
#define DIGITAL2 49
#define DIGITAL3 47
#define ANALOG1 15
#define ANALOG2 13
// ***                        ****

extern boolean isactive;
extern boolean tabelle;
extern boolean MessungDurchfuehren;
extern int tolPercent;
extern int stufeK;
extern int backK;
extern int sIndex;
extern int sIndex2;
extern int posK;
extern int index;
extern boolean allowInput;

#ifndef UNO
#include <BigNumber.h>
extern const BigNumber p_max PROGMEM;  // 5 W/m^2
extern const BigNumber zero PROGMEM;
extern const BigNumber eins PROGMEM;
extern const BigNumber vier PROGMEM;
extern const BigNumber zehn PROGMEM;
extern const BigNumber neunzehn PROGMEM;
extern const BigNumber vierunddreissig PROGMEM;
extern const BigNumber hundert PROGMEM;
extern const BigNumber materialien[][7] PROGMEM;
extern const char* symbole[];

extern const BigNumber minus_eins;
extern const BigNumber l_inc;
extern const BigNumber l_min;
extern const BigNumber l_max;
extern const BigNumber h;
extern const BigNumber c;
extern const BigNumber elementarladung;
extern const BigNumber nano;
extern int m_index;
extern BigNumber ausloesearbeit;
extern BigNumber ausbeute;
extern BigNumber wellenlaenge;
#endif
