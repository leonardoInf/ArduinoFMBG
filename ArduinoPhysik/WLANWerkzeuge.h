void sendWifi(){
  
}

int WLANBefehlErhalten(){
  Serial.print('s');
  delay(120);
  char key = Serial.read();
  while(Serial.available()){Serial.read();}
  switch(key){
          case 'S':
            return btnSELECT;
          case 'D':
            return btnDOWN;
            return btnUP;
          case 'B':
            return btnLEFT;
          case 'N':
            return btnRIGHT;

          default:
            return btnNONE;
        }
}
