int kondensatorProzentBerechnen(int inc){
  
    digitalWrite(DIGITAL1, HIGH);
    while(analogRead(ANALOG1) < 102*inc){;}
    if(inc == 6){
        while(analogRead(ANALOG1) < 632 + (8-sIndex)*10){;}
      }
    if(analogRead(ANALOG1) >= 1020){
      while(analogRead(ANALOG1) < 1023){;}
      digitalWrite(DIGITAL1, LOW);
    }
    return 10*inc;
  }

void kondensator(){
  char prozent_buf[5];
  char abweichung_buf[5];
  char inc_buf[5];
  char tau_buf[7];
  char ladeZeit_buf[7];
  char kapazitaet_buf[10];
  char sIndex_buf[2];
  static int selfInc = 0;
  static int previousProzent;
  static int abweichung;
  static long tau;
  static unsigned long widerstand;
  const char *widerstaende[5] = {
              "1000\364", "10k\364", "47k\364",
              "100k\364", "1M\364"
    };
  const unsigned long widerstaendeLong[5] = {
              (unsigned long)1000, (unsigned long)10e3, (unsigned long)47e3, (unsigned long)100e3, (unsigned long)1000e3
    };

  static unsigned long long ladeZeit = 0;
  int prozent;
  if(aktivieren()){
        pinMode(DIGITAL1, OUTPUT);
    }
  
  if(posK == 0){
  strcpy(str_result, "U(t) und C      ;");
  strcat(str_result, "Start mit SEL");
  }


  if(posK == 1){
    strcpy(str_result, "R ausw\341hlen(SEL);");
    strcat(str_result, widerstaende[sIndex]);
    strcat(str_result, " (");
    itoa(sIndex+1, sIndex_buf, 10);
    strcat(str_result, sIndex_buf);
    strcat(str_result, "/5)          ");
  }

  if(posK == 2){
    strcpy(str_result, "Abweichung:");
    abweichung = sIndex2 * 50;
    itoa(abweichung, abweichung_buf, 10);
    strcat(str_result, abweichung_buf);
    strcat(str_result, "    ;                ");  
  }


  if(posK == 3){
    if(previousProzent != 100){
    strcpy(str_result, "}Lade.. ");
    unsigned long long t = millis();
    prozent = kondensatorProzentBerechnen(selfInc);
    ladeZeit += millis()-t;
    if(selfInc == 6){
        allowInput = true;
        tau = ladeZeit;
      }
    previousProzent = prozent;
    itoa(prozent, prozent_buf, 10);
    strcat(str_result, prozent_buf);
    strcat(str_result, " \45");
    selfInc++;
    return;
    }
    else{
      //tau = (ladeZeit/5);
      strcpy(str_result, "Fertig!        ;");
      strcat(str_result, "Dr\365cken Sie SEL");
      return;
    }
  }

 if(posK == 4){
    widerstand = widerstaendeLong[sIndex]-abweichung;
    double kapazitaet = tau/(double)widerstand;
    long kapazitaetuF = kapazitaet * 1e3;
    /*strcpy(str_result, "Zeit: ");
    itoa(ladeZeit, ladeZeit_buf, 10);
    strcat(str_result, ladeZeit_buf);
    strcat(str_result, " ms");*/
    strcpy(str_result, "5(1-e(-t/");
    String(tau/(float)1000, 2).toCharArray(tau_buf, 7);
    strcat(str_result, tau_buf);
    strcat(str_result, "));C: ");
    String(kapazitaetuF).toCharArray(kapazitaet_buf, 10);
    strcat(str_result, kapazitaet_buf);
    strcat(str_result, "\344F          ");
    return;  
  }

  if(posK == 5){
    isactive = false;
    allowInput = true; 
   }
}
