void hallsensor(){
   aktivieren();
   float spannung = 3;
   char flussdichte_buf[6];
   spannung = analogRead(ANALOG1)-80;
   Serial.println(spannung);
   spannung = HALL_A_REF-spannung;
   spannung *= .004736; //Umwandlung in Volt
   float flussdichte = (float)HALL_M * spannung + HALL_N;
   if(abs(int(flussdichte)) == 2 || abs(int(flussdichte)) == 3) flussdichte = 0;
   itoa(flussdichte, flussdichte_buf, 10);
   strcpy(str_result, "B: ");
   strcat(str_result, flussdichte_buf);
   strcat(str_result, "mT      ");
   delay(100);
}
