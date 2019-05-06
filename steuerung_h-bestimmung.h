if(lcd_key == btnDOWN && wellenlaenge > l_min)
	wellenlaenge -= l_inc;
       
if(lcd_key == btnUP && wellenlaenge < l_max)
        wellenlaenge += l_inc;

if(lcd_key == btnSELECT){
	if(m_index == 6) m_index = 0;
        else m_index++;
       	ausloesearbeit = materialien[0][m_index];
        ausloesearbeit *= elementarladung;  //eV -> J
        ausbeute = materialien[1][m_index]; 
}

if(VerlassenPruefen(key)) return true;
