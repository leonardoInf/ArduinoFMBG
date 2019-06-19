void lcdLeeren(){
  #ifndef I2CLCD
  lcd.clear();
    #else
    lcd.clearDisplay();
    #endif
}

void ZeilenUmbruch(){
  #ifndef I2CLCD
  lcd.setCursor(0,1);
  #else
  lcd.print("\n");
  #endif  
}

void lcdInitialisieren(){
    lcd.setCursor(0,0);
    #ifdef I2CLCD
    lcd.clearDisplay();
    #endif
}

void lcdAusgabe(const char str[], int newlines){
  lcdInitialisieren();
  for(int i = 0; i<strlen(str); i++){
     char c = str[i];
     if(c == ';'){
        ZeilenUmbruch();
     }

     else if(c == '}'){
        lcdLeeren(); 
     }
     
     else if(c != 0 && c!= -1){
        lcd.print(c);
        #ifdef SERIELLE_AUSGABE
        Serial.print(c);
        #endif 
     }
     else newlines = -1;
  }
  #ifdef SERIELLE_AUSGABE
  if(newlines >= 0){
    for(int i=0;i<newlines;++i){
      Serial.println("");  
    }
  }
  #endif
  
  #ifdef I2CLCD
  lcd.display();
  #endif
}
