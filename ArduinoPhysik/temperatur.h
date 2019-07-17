void temperatur(){
  double temperatur;
  int luftfeuchtigkeit;
  char temperatur_buf[6];
  char luftfeuchtigkeit_buf[4];
  static DHT_Unified dht(DIGITAL1, DHT11);

 if(aktivieren()){
      dht.begin();
    }
  
  sensors_event_t event;              //Speicherstelle für event
  dht.temperature().getEvent(&event); //Zeiger auf event übergeben
  temperatur = event.temperature;     //Temperatur auslesen, ergibt NaN wenn kein DHT11 angeschlossen ist
  dht.humidity().getEvent(&event);
  luftfeuchtigkeit = event.relative_humidity;
  
  strcpy(str_result, "T: ");
  if(!isnan(temperatur)){     //Das Sketch hängt sich auf, wenn man dtostrf 'NaN' als Argument übergibt
    dtostrf(temperatur, anzahlStellen(temperatur)+3, 2, temperatur_buf);
  }
  else strcpy(temperatur_buf, "0");
  strcat(str_result, temperatur_buf);
  strcat(str_result, " \337C            ;H: ");
  itoa(luftfeuchtigkeit, luftfeuchtigkeit_buf, 10);
  strcat(str_result, luftfeuchtigkeit_buf);
  strcat(str_result, " \45             ");
}
