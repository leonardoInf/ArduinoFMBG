//#if defined(WLAN) || defined(SERIELLE_AUSGABE) 
  Serial.begin(9600);
  DIDR0 = 0; DIDR2 = 0;       //Analoge Pins konfigurieren
  //#endif
  #ifdef SERIELLE_AUSGABE
  Serial.println("zSerial alive");
  #endif
  #ifndef I2CLCD
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  #else
  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  lcd.clearDisplay();
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2);
  lcd.print("Arduino\nFMBG");
  lcd.display();
  delay(800);
  lcd.clearDisplay();
  lcd.setCursor(0,0);
  lcd.setTextSize(1);;
  lcd.display();
  #endif
  lcdAusgabe(optionen[index], 1);
  #ifdef ERWEITERT
  Wire.begin();
  #endif
  #ifndef UNO
  randomSeed(analogRead(A9));
  #else
  randomSeed(analogRead(A1));
  #endif
  //die ersten zwei Werte überpringen
  for(int i = 0; i<2; ++i)
      random(0,50-1);
  
