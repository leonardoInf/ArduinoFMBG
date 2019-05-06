char * spannungsteiler(){
  static int score = 0;
  static int randIndex = random(0,50-1);

  static int expectedInts[50] = {710, 415, 697, 951, 386, 630, 
                        724, 655, 500, 164, 284, 323,
                        556, 778, 503, 912, 558, 740, 
                        618, 564, 647, 451, 658, 514,
                        477, 377, 761, 230, 581, 155,
                        930, 902, 210, 381, 122, 100,
                        155, 653, 201, 458, 398, 127,
                        437, 118, 674, 521, 492, 917,
                        958, 59};
                        
                        
                        
 static char *voltages[50] = {  "3,43", "2,01", "3,37", "4,60", "1,87", 
                        "3,05", "3,50", "3,17", "4,89", "0,79",
                        "1,37", "1,56", "2,69", "3,76", "2,43",
                        "4,41", "2,70", "3,58", "2,99", "4,89",
                        "3,13", "2,18", "3,18", "2,48", "2,31",
                        "1,82", "3,68", "4,94", "2,81", "0,75", 
                        "4,50", "4,36", "1,02", "1,84", "0,59",
                        "0,48", "0,75", "3,16", "0,97", "2,21",
                        "1,92", "0,61", "2,11", "0,57", "3,26",
                        "2,52", "2,38", "4,43", "4,63", "2,88"};

  int aRead = analogRead(ANALOG1);
  int expected = expectedInts[randIndex];
  //Serial.println(aRead-expected);
  int tol = 1023 * (tolPercent/(float)100);
  if(abs(aRead-expected) <= tol){
     score++;
     randIndex = random(0,50-1);
  }
  char str_result[40];
  char scr_buf[4];
  char tol_buf[5];
  aktivieren();
  
  strcpy(str_result, "Erwarte: "); 
  strcat(str_result, voltages[randIndex]);
  strcat(str_result, " V");
  strcat(str_result, ";"); //Zeilenumbruch
  strcat(str_result, "Tol:");
  itoa(tolPercent, tol_buf, 10);
  strcat(str_result, tol_buf);
  strcat(str_result, "\45 ");
  strcat(str_result, "Scr:");
  itoa(score, scr_buf, 10);
  strcat(str_result, scr_buf);
  strcat(str_result, "   ");
  return str_result;
  //memset(str_result, 0, 40);
}
