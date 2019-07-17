void wetter(){
    char esp_in[10];
    char str_result[40];
    short tindex = 0;
    aktivieren();
    //str_result[0] = '}';
    Serial.print('w');
    delay(1000);
    int av = Serial.available();
    if(av == 0){
      strcpy(str_result, "Verbinde..      ");
      return str_result;
      }
    for( int i = 0; i < av; i++){
          char c = Serial.read();
          if(isdigit(c) || c == ',' || c == '>'){
            if(c == '>') tindex = i;
            else esp_in[i] = c;
          }
      }
    strcpy(str_result, "T: ");
    strncat(str_result, esp_in, tindex);
    strcat(str_result, " \337C          ;H: ");
    memmove(esp_in, esp_in+tindex, strlen(esp_in)-tindex + 1);
    strcat(str_result, esp_in);
    strcat(str_result, " \45     ");
}
