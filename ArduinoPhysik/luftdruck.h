//leicht modifiziert aus: Beispiele-BMP180-BMP180_test
double getPressure(SFE_BMP180 *pressure)
{
  char status;
  double T,P,p0,a;
  status = (*pressure).startTemperature();
  if (status != 0)
  {
    delay(status);
    status = (*pressure).getTemperature(T);
    if (status != 0)
    {
      status = (*pressure).startPressure(3);
      if (status != 0)
      {
        delay(status);

        status = (*pressure).getPressure(P,T);
        if (status != 0) return(P);
        else return 0.0;
      }
  }
 }
}


double getTemperature(SFE_BMP180 *temperature){
    char status;
    double T;
    status = (*temperature).startTemperature();
    if(status != 0){
      delay(status);
      status = (*temperature).getTemperature(T); 
    }
    if(status != 0) return T;
    else return 0.0;
}

// ****                                 *****
void luftdruck(){
    char luftdruck_buf[8];
    char temperatur_buf[6];
    static SFE_BMP180 sensor;
    double luftdruck;
    double temperatur;
    
    if(aktivieren()){
        sensor.begin();
    }
                
    strcpy(str_result, "P: ");
    luftdruck = getPressure(&sensor);     //Zeiger auf den Sensor
    dtostrf(luftdruck, anzahlStellen(luftdruck)+1, 1, luftdruck_buf);
    strcat(str_result, luftdruck_buf);
    strcat(str_result, " hPa     ;T: ");
    temperatur = getTemperature(&sensor);
    dtostrf(temperatur, anzahlStellen(temperatur)+1, 1, temperatur_buf);
    strcat(str_result, temperatur_buf);
    strcat(str_result, "\337C");
 }
