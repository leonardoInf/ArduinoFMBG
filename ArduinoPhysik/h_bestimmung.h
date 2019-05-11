double handleSpannung(){
   static int vorheriges = 3000; //(unmöglicher) Startwert
   static double spannung;
   int aread = analogRead(ANALOG1);
   
   if(vorheriges != 3000){   //vehindern, dass am Anfang Zustände blockiert werden
   if(abs(aread-vorheriges) >= 2)
      spannung = map(aread, 0, 1023, 0, 3500)/(double)1000;
   }
   else spannung = map(aread, 0, 1023, 0, 3500)/(double)1000;
   if(spannung >= 2095) spannung = 3000; //"haken" bei 99% verhindern   
   vorheriges = aread;
   return spannung;
}

int handleLeistung(){
  static int vorheriges = 150; //(unmöglicher) Startwert
  static int intensitaet;
  int aread = analogRead(ANALOG2);

  if(vorheriges != 150){
    if(abs(aread-vorheriges) >= 2)
      intensitaet = map(aread, 0, 1023, 0, 100); //100% = 5 W*m^-2
  }
  else intensitaet = map(aread, 0, 1023, 0, 100);
  if(intensitaet == 99) intensitaet = 100; //"haken" bei 99% verhindern
  vorheriges = aread;
  return intensitaet;
}

double handleFotostrom(){
    // zurzeitige Gegenspannung speichern;
    BigNumber spannung = handleSpannung();
    //spannung *= minus_eins;

    //Frequenz
    BigNumber frequenz = c/wellenlaenge;

    //Strahlungsleistung
    BigNumber strahlungsleistung = handleLeistung();
    strahlungsleistung /= hundert;
    strahlungsleistung *= p_max;

    //Kathodenfläche
    BigNumber flaeche = 2;  
    flaeche /= zehn.pow(vier); //2 cm^2

    //Leistung
    BigNumber leistung = strahlungsleistung*flaeche;;

    //maximaler Photostrom
    BigNumber i_max = ausbeute * leistung * elementarladung/(h*frequenz);
    //benötigte Gegenspannung = E_kin_max
    BigNumber gegenspannung = h*frequenz-ausloesearbeit;
    gegenspannung /= elementarladung;;
    if(gegenspannung.isZero() || gegenspannung.isNegative()) //Vergrößerung des Photostroms verhindern
        return 0;  

    //zurzeitiger Photostrom
    double numerus_d = double(i_max)+1;
    double i_log = log(numerus_d);
    BigNumber exponent = i_log;
    exponent /= gegenspannung;
    exponent *= spannung;
    BigNumber i_von_u =  (i_max+eins) - BigNumber(exp(exponent));
    i_von_u *= zehn.pow(6);   //A -> uA
    Serial.print(i_max+eins);
    Serial.print(" - exp(");
    Serial.print(i_log, 10);
    Serial.print("/");
    Serial.print(gegenspannung);
    Serial.print("*");
    Serial.print(spannung);
    Serial.print(") = ");
    Serial.println(i_von_u);
    return double(i_von_u);
}


char * h_bestimmung(){
    if(aktivieren()){
          BigNumber::begin(38);
          h = 6.626;
          h /= zehn.pow(vierunddreissig);
          c = "299792458";    //Zeichenketten für BigNumbers dürfen nicht mit F gekennzeichnet werden
          elementarladung = 1.602;
          elementarladung /= zehn.pow(neunzehn);
          ausloesearbeit = materialien[0][m_index];
          ausloesearbeit *= elementarladung;
          ausbeute = materialien[1][m_index];
          nano = zehn.pow(9);
          wellenlaenge = 400;
          wellenlaenge /= nano;
          l_inc = 25;
          l_inc /= nano;
          l_min = 200;
          l_min /= nano;
          l_max = 800;
          l_max /= nano;
          minus_eins = -1;
      }
    
   char str_result[40];
   char spannung_buf[5];
   char intensitaet_buf[4];
   char wellenlaenge_buf[6];
   char stromstaerke_buf[7];
   int intensitaet = handleLeistung();
   strcpy(str_result, "U: ");
   dtostrf(handleSpannung(), 4, 2, spannung_buf);
   strcat(str_result, spannung_buf);
   strcat(str_result, "V I:");
   float stromstaerke = runden(handleFotostrom(), 1);
   int b_size = anzahlStellen(stromstaerke)+2; 
   dtostrf(stromstaerke, b_size, 1, stromstaerke_buf);
   strcat(str_result, stromstaerke_buf);
   strcat(str_result, " ;");
   itoa(intensitaet, intensitaet_buf, 10);
   strcat(str_result, intensitaet_buf);
   if(intensitaet < 100)
      strcat(str_result, "\45  ");
   else strcat(str_result, "\45 ");
   strcat(str_result, "\250:");
   itoa(long(wellenlaenge*nano), wellenlaenge_buf, 10);
   strcat(str_result, wellenlaenge_buf);
   strcat(str_result, "nm ");
   strcat(str_result, symbole[m_index]);
   strcat(str_result, "  ");
   return str_result;
}
