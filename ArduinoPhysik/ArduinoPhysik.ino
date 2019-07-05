/* Sketch für ArduinoFMBG
 * Leonardo Braguinski, 5. PK Physik/Informatik
*/
#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega328P__)
#include "wichtig.h"
#include "externeSensoren.h"
#include "steuerung.h"
#include "WLANWerkzeuge.h"
#include "lcdWerkzeuge.h"

// ***                                    ****

void setup() {
  #include "setup.h"
}

void loop() {
  #include "loop.h"
}
#else 
void setup(){}
void loop(){}
#endif
