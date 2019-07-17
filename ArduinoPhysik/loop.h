#ifdef WLAN
  lcd_key = WLANBefehlErhalten();
  if(lcd_key == 5){ 
    lcd_key = read_LCD_buttons();
  }
  #else
    lcd_key = read_LCD_buttons();
  #endif

if(rcvMode){
        memset(str_result, 0, 40);     //globales str_result Array mit Nullen füllen (leeren)
        if(index > 10)
          screenErhalten();
       else lokalAusfuehren();
       lcdAusgabe(str_result, 3);
       #ifdef WLAN
       sendWifi();
       #endif
       if(KeypadPruefen(lcd_key)){
          lcdLeeren();
          lcdAusgabe(optionen[index], 1);
          return;       //verhindern, dass zusätzlich noch die Eingaben im menu mode abgearbeitet werden
        }
    }
  
  if(buttonPressed(lcd_key) && !isactive){
    lcdLeeren();
    
    if(lcd_key == btnRIGHT){
        if(index == anzahlOptionen-1) index = 0;
        else index++;
        if(rcvMode){
            rcvMode = false;
            //index = 0;
        }
    }
    
    if(lcd_key == btnLEFT){
       if(index == 0) index = anzahlOptionen-1;
       else index--;
       if(rcvMode){
            rcvMode = false;
            //index = 0;
        }
      }

    if(lcd_key == btnSELECT){
        lcdLeeren();
        rcvMode = true;
        lcd_key = btnNONE;
    }
    
    else if(lcd_key != btnSELECT)
      if(!rcvMode)
      lcdAusgabe(optionen[index], 1);
  }
   //delay(120);
