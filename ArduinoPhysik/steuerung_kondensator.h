posK = stufeK-backK;
if(posK == 0){
	if(VerlassenPruefen(key)){
        return true;
        }
}
      
if(key == btnUP){
        if(posK == 1 && sIndex < 4) sIndex++;
        if(posK == 2 && sIndex < 20) sIndex2++; 
}

if(key == btnDOWN){
        if(posK == 1 && sIndex > 0) sIndex--;
        if(posK == 2 && sIndex > -20) sIndex2--; 
}

if(key == btnRIGHT){
        if(posK == 4) stufeK++;
        posK = stufeK-backK;
        if(posK == 3) allowInput = false;
}

if(key == btnLEFT){
        if(posK != 3) backK++;
        posK = stufeK-backK;
        if(posK == 3) allowInput = false;
        return true;
}

if(key == btnSELECT){
        if(posK != 4) stufeK++;
}
