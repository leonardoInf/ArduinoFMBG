/*
   Globale Variablen für die Arduino-Messbox
   Leonardo Braguinski, 5. PK Physik/Informatik
*/

// ***  zusätzliche Optionen   ****
//#define ERWEITERT
#if defined(__AVR_ATmega328P__)     //Wenn Arduino UNO als Board ausgewählt wurde 
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

extern char str_result[40];
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
extern const BigNumber p_max;  // 5 W/m^2
extern const BigNumber zero;
extern const BigNumber eins;
extern const BigNumber vier;
extern const BigNumber zehn;
extern const BigNumber neunzehn;
extern const BigNumber vierunddreissig;
extern const BigNumber hundert;
extern const BigNumber materialien[][7];
extern const char* symbole[];

extern BigNumber minus_eins;
extern BigNumber l_inc;
extern BigNumber l_min;
extern BigNumber l_max;
extern BigNumber h;
extern BigNumber c;
extern BigNumber elementarladung;
extern  BigNumber nano;
extern int m_index;
extern BigNumber ausloesearbeit;
extern BigNumber ausbeute;
extern BigNumber wellenlaenge;
#endif
