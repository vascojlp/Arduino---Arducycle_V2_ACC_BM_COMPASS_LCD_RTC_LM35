void LCD_boot(){
  
// Clear the screen and draw the frame
  
  myGLCD.setFont(BigFont);
  myGLCD.clrScr();
  myGLCD.setBackColor(0, 0, 0);                      //preto                 
  
  myGLCD.setColor(126,188,209);                      //azul claro
  myGLCD.print("BOOTING ...", 5, 110);
  delay(500);
  myGLCD.print("BOOTING .......", 5, 110);
  delay(500);
  myGLCD.print("BOOTING ............", 5, 110);
  delay (1000);
  
  myGLCD.clrScr();
  myGLCD.setColor(255, 255, 255);                    //branco
  myGLCD.drawRect(0,0,318,238);  
  myGLCD.print("ARDUCYCLE V 1.2", CENTER, 80);  //center,100
  delay(500);
  myGLCD.print("YAMAHA XV 535 DXS", CENTER, 160);  
  delay (3000);
  
  
  
  }

