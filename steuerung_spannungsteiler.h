if(key == btnDOWN){
	if(tolPercent > 2 && tolPercent <= 10)
        tolPercent--;
	else tolPercent = 10;
}
if(key== btnUP){
	if(tolPercent < 10 && tolPercent >= 2)
		tolPercent++;
      	else tolPercent = 2;
}

if(VerlassenPruefen(key)){
        return true;
}
