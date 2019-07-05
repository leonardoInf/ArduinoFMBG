boolean VerlassenPruefen(char key){
    if(key == btnLEFT && allowInput){
          isactive = false;
          rcvMode = false;
          #ifdef SERIELLE_AUSGABE
          Serial.println(index);
          #endif
          return true; 
       }
   return false;
}

#ifndef UNO
boolean handleKeypad(char key){
	if(index == 0 && allowInput){	//Temperatur
		#include "steuerung_temperatur.h"
	}

	if(index == 1 && allowInput){	//Hall-Sensor
		#include "steuerung_hallsensor.h"
	}

	if(index == 2 && allowInput){	//h-Bestimmung
		#include "steuerung_h-bestimmung.h"
	}

	if(index == 3 && allowInput){	//Pendel
		#include "steuerung_pendel.h"
	}

	if(index == 4 && allowInput){	//Schall
		#include "steuerung_schall.h"
	}   

	if(index == 6 && allowInput){  //Spannungsteiler
      if(index == 5 && allowInput){  //Luftdruck
    #include "steuerung_luftdruck.h"
  }		#include "steuerung_spannungsteiler.h"
  }

  if(index == 7 && allowInput){  //Kondensator
		      #include "steuerung_kondensator.h"
  }

  if(index == 8 && allowInput){  //Wetter
          #include "steuerung_wetter.h"
  }

    else if(VerlassenPruefen(key)) return true;  

    return false;
}
#else 
boolean handleKeypad(char key){
  if(index == 0 && allowInput){ //Temperatur
    #include "steuerung_temperatur.h"
  }
  if(index == 1 && allowInput){  //Luftdruck
    #include "steuerung_luftdruck.h"
  }

  if(index == 2 && allowInput){  //Pendel
    #include "steuerung_pendel.h"
  }

  if(index == 3 && allowInput){  //Schall
    #include "steuerung_schall.h"
  }
}
#endif

  
