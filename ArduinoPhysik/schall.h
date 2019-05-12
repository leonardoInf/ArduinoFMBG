//modifiziert aus: https://blog.yavilevich.com/2016/08/arduino-sound-level-meter-and-spectrum-analyzer/
double MeasureVolume()
{
    const int anzahlSamples = 335;  //35 ms (I)
    const float p_ref = .1;
    double spl = 0;
    
    long soundVolAvg = 0, soundVolMax = 0, soundVolRMS = 0, t0 = millis();
    for(int j = 0; j<10; j++){
    for (int i = 0; i < anzahlSamples; i++)
    {
        while (!(ADCSRA & _BV(ADIF)));
        ADCSRA |= _BV(ADIF);
        byte m = ADCL;
        byte j = ADCH;
        int k = ((int)j << 8) | m;
        int amp = abs(k-512);
        soundVolRMS += ((long)amp*amp);
    }
    
    soundVolRMS /= anzahlSamples;
    soundVolRMS = sqrt(soundVolRMS);
    spl += 20*log10(soundVolRMS/p_ref);
    
    }
    spl /= 10.0;
    Serial.print("davor: ");
    Serial.println(spl);
    float percent = map(spl, 46, 66, 0, 100);
    if(spl > 54) percent *= 50.0/60*2;
    spl += percent/100.0*20;
    if(spl > 56) spl += 5;
    Serial.print("danach: ");
    Serial.println(spl);
    return spl;
}
//*******                         *****                  

char * schall(){
    if(aktivieren()){
      Serial.println("aktiviert");
      DIDR0 = 0; DIDR2 = 0;   //digitale Eingänge für analoge Pins deaktivieren           
      ADMUX |=  ANALOG1 % 8;
      ADMUX |= _BV(REFS0);  //ARef = 5V
      if(ANALOG1 > 7) ADCSRB |= _BV(MUX5);
      //Samplingrate auf 38,46 kHZ setzen, Quelle: https://blog.yavilevich.com/2016/08/arduino-sound-level-meter-and-spectrum-analyzer/
      ADCSRA |=  5;
      ADCSRA |= _BV(ADEN);
      ADCSRA |= _BV(ADSC);   //beim Free-Running-Modus muss ADSC nur einmalig gesetzt werden
      /*Auswahl des Free-Runnnig-Modus ermöglichen 
      * siehe: AtMega2560 Handbuch S. 287 
      * */
      ADCSRA |= _BV(ADATE);
   }
    char str_result[40];
    char spl_buf[5];
    char p_buf[10];
    double spl = MeasureVolume();
    double p = potenzieren(10, spl/20)*.00002;
    const int spl_min = 53;
    const int spl_max = 77;
    
    strcpy(str_result, "p: ");
    if(spl < spl_max && spl > spl_min){
        dtostrf(p*1000, anzahlStellen(p)+4, 4, p_buf);
        strcat(str_result, p_buf);
        strcat(str_result, " mPa   ;SPL: ");
        }
    else if(spl >= spl_max) {
      strcat(str_result, " MAX            ;SPL: ");
    }
    else{
      strcat(str_result, " MIN            ;SPL: ");
    }
    
    if(spl < spl_max && spl > spl_min){
         itoa(int(spl), spl_buf, 10);
         strcat(str_result, spl_buf);
         strcat(str_result, " dB ");
         }
    else if(spl >= spl_max){ 
         strcat(str_result, "MAX       ");
    }
    else{
        strcat(str_result, "MIN       ");
      }
    return str_result; 
}
