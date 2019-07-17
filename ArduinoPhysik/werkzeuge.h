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
      return true;
      
  }   else return false;
}
