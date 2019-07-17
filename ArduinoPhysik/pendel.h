float frequenzMessen(int d_max){
    UltraSonicDistanceSensor sensor(DIGITAL1, DIGITAL2);
    long long periodendauern = 0;
    long long t1 = 0;
    
    for(int i = 0; i<10; i++){
    double d = 255;
    long long t0 = millis();
    while(d>d_max){
        d = sensor.measureDistanceCm();
        if(millis()-t0 >= 10000) return 0.0;  
    };
    if(millis()-t0 <= 50){periodendauern += millis()-t0; i--; continue;}
    if(i > 0) periodendauern += millis() - t0+200;
    digitalWrite(DIGITAL3, LOW);
    delay(200);
    digitalWrite(DIGITAL3, HIGH);
  }
    periodendauern /= 9;   //arithmetisches Mittel
    double periodendauer_d = (periodendauern)/(double)1000; //ms -> s
    return 1/(2*(float)periodendauer_d);  //Frequenz
}


void pendel(){
  char max_abstand_buf[5];
  static char frequenz_buf[8];
  char n_buf[2];
  float frequenz;
  static int n = 0;
  static float frequenzen[3];
  char mittelwert_buf[7];
  //static boolean benachrichtigt = false;

  if(aktivieren()){
      tabelle = false;
      pinMode(DIGITAL3, OUTPUT);
      digitalWrite(DIGITAL3, HIGH);
  }

  if(n == 3){
      tabelle = true;  
  }
  
  strcpy(str_result, "d_max:");
  int aread = analogRead(ANALOG1);
  int max_abstand = map(aread, 0, 1023, 2, 99); 
  itoa(max_abstand, max_abstand_buf, 10);
  strcat(str_result, max_abstand_buf);
  strcat(str_result, "cm");
  for(int i = 0; i<3-anzahlStellen(max_abstand); i++) strcat(str_result, " ");
  strcat(str_result, "n=");
  itoa(n, n_buf, 10);
  strcat(str_result, n_buf);
  strcat(str_result, "/3;f: ");
  
  if(MessungDurchfuehren){
      Serial.println("Messe..");
      tabelle = false;
      //benachrichtigt = false;
      if(n%3 == 0) n = 0;
      n++;
      digitalWrite(DIGITAL3, LOW);
      delay(1500);
      digitalWrite(DIGITAL3, HIGH);
      frequenz = frequenzMessen(max_abstand);
      frequenzen[n-1] = frequenz;
      dtostrf(frequenz, anzahlStellen(frequenz)+2, 2, frequenz_buf);
      MessungDurchfuehren = false;
      allowInput = true;
      }
  strcat(str_result, frequenz_buf);
  if(!tabelle)
  strcat(str_result, "Hz       ");
  
  if(tabelle){
    strcat(str_result, "Hz \370:");
    float durchschnitt = 0;
    for(int i=0; i<sizeof(frequenzen)/sizeof(float); i++)
        durchschnitt += frequenzen[i];
    durchschnitt /= sizeof(frequenzen)/sizeof(float);
    dtostrf(durchschnitt,4, 2, mittelwert_buf);
    strcat(str_result, mittelwert_buf);
  }
}
