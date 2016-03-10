void Ignicion() {
  
 Val= digitalRead(IGNICION);
  
  if(Val == HIGH ) {
    myGLCD.lcdOn(); }
    else { 
      myGLCD.lcdOff(); } 
      
   }

