void temperatur(){
  float temperatur;
  int luftfeuchtigkeit;
  char temperatur_buf[6];
  char luftfeuchtigkeit_buf[4];
  static DHT_Unified dht(DIGITAL1, DHT11);

  if(aktivieren()){
      dht.begin();
    }
  
  sensors_event_t event;              //Speicherstelle für event
  dht.temperature().getEvent(&event); //Zeiger auf event übergeben
  temperatur = event.temperature;     //Temperatur auslesen
  dht.humidity().getEvent(&event);
  luftfeuchtigkeit = event.relative_humidity;
  
  strcpy(str_result, "T: ");
  String(temperatur, 2).toCharArray(temperatur_buf, 6);
  strcat(str_result, temperatur_buf);
  strcat(str_result, " \337C            ;H: ");
  itoa(luftfeuchtigkeit, luftfeuchtigkeit_buf, 10);
  strcat(str_result, luftfeuchtigkeit_buf);
  strcat(str_result, " \45             ");
}
