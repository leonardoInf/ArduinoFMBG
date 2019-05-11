#ifdef WLAN
  lcd_key = WLANBefehlErhalten();
  if(lcd_key == 5){ 
    lcd_key = read_LCD_buttons();
  }
  #else
    lcd_key = read_LCD_buttons();
  #endif
  
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
  
    if(rcvMode){
       char screen[40];
       if(index > 10)
          screenErhalten(screen);
       else lokalAusfuehren(screen);
       lcdAusgabe(screen, 3);
       #ifdef WLAN
       sendWifi(screen);
       #endif
       if(handleKeypad(lcd_key)){
          lcdLeeren();
          lcdAusgabe(optionen[index], 1);
        }
    }
   //delay(120);
