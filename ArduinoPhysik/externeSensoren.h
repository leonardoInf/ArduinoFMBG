void screenErhalten(){
  #ifdef ERWEITERT
  memset(screen, 0, 33);
  Wire.requestFrom(2+index, 32);
     if(Wire.available()){
         int i = 0;
         while(Wire.available()){
            char c = Wire.read();
            screen[i] = c;
            i++;
     }
  }
  #endif 
}
