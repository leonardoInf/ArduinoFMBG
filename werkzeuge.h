 //Quelle: https://stackoverflow.com/a/14003560/6455909
 double runden(double x, unsigned int digits) {
    double fac = pow(10, digits);
    return round(x*fac)/fac;
 }

//Quelle: https://stackoverflow.com/a/1306751/6455909
 int anzahlStellen(double n){
    if (n == 0) return 1;
    else return int(log10(int(n))+1);
}

 int anzahlStellen(int n){
    if (n == 0) return 1;
    else return int(log10(n)+1);
}

double potenzieren(double basis, double exponent, boolean E=false){
      if(!E)  return exp(log(basis)*exponent);
      else    return exp(exponent);  
}

int ledBlinken(int n, int pin, boolean polung, int v){
    for(int i = 0; i<n; i++){
      digitalWrite(pin, polung);
      delay(v);
      digitalWrite(pin, !polung);
      delay(v);
    }
}

//Sensoren aktivieren
boolean aktivieren(){
    if(!isactive){
        isactive = true;
        allowInput = true;
        #ifdef SERIELLE_AUSGABE
        switch(index){
           case 0:
              Serial.print("Spannungsteiler"); break;
           case 1:
              Serial.print("Kondensator"); break;
           case 2:
              Serial.print("Temperatur"); break;
           case 3:
              Serial.print("Hall-Sensor"); break;
           case 4:
              Serial.print("h-Bestimmung"); break;
           case 5:
              Serial.print("Fadenpendel"); break;
           case 6:
              Serial.print("Schall"); break;
           case 7:
              Serial.print("Wetter");; break;
           default:
             ; 
      }
      Serial.println(" ausgewählt");
      #endif
      return true;
      
  }   else return false;
}
