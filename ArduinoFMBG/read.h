 /* Header Datei, um Tasten einzulesen
 * Erweitert, Original: https://www.velleman.eu/downloads/29/vma203_a4v02.pdf
 * */

 #include "globals.h"
 #include <Keypad.h>

int lcd_key = 0;
boolean extraKeypad = true;
enum{ btnRIGHT = 0, btnUP = 1, btnDOWN = 2, btnLEFT = 3, btnSELECT = 4, btnNONE = 5};
//1x5 Matrix
#ifndef VIER_TASTEN_MATRIX
char hexaKeys[1][5] = {
  {'S', 'D', 'I', 'B', 'N'}
};
#else
char hexaKeys[1][3] = {
  {'B', 'S', 'N'}
  };
#endif

#if !defined(UNO) && !defined(VIER_TASTEN_MATRIX)
byte rowPins[1] = {32}; 
byte colPins[5] = {30, 28, 26, 24, 22};
#endif

#if defined(UNO) && !defined(VIER_TASTEN_MATRIX)
byte rowPins[1] = {2}; 
byte colPins[5] = {3, 4, 5, 6, 7};
#endif

#if defined(UNO) && defined(VIER_TASTEN_MATRIX)
byte rowPins[1] = {3}; 
byte colPins[3] = {6, 7, 5};
#endif

#ifndef VIER_TASTEN_MATRIX
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 1, 5);
#else
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 1, 3);
#endif

int read_LCD_buttons(){
  char key = customKeypad.getKey();
  if(extraKeypad){
    if(key){
      switch(key){
          case 'S':
            return btnSELECT;
          case 'D':
            return btnDOWN;
          case 'I':
            return btnUP;
          case 'B':
            return btnLEFT;
          case 'N':
            return btnRIGHT;
        }
    }
  }

  #ifndef I2CLCD
	int adc_key_in = analogRead(0);
	if(adc_key_in > 1000) return btnNONE;
  else  delay(200);
	if(adc_key_in < 50) return btnRIGHT;
	if(adc_key_in < 250) return btnUP;
	if(adc_key_in < 400) return btnDOWN;
	if(adc_key_in < 600) return btnLEFT;
	if(adc_key_in < 800) return btnSELECT;
	return btnNONE;
  #endif
}

boolean buttonPressed(int val){
		return val !=5;
}
