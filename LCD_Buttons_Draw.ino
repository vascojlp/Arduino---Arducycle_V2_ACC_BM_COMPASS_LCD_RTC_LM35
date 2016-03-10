void drawButtons()
{
  
  
   ///--- Botao reset
  myGLCD.setFont(SmallFont);
  myGLCD.setColor(255, 255, 255);                    //branco 
  myGLCD.drawRoundRect(135, 1, 185, 30);
  myGLCD.fillRoundRect(136, 2, 184, 29);
  myGLCD.print("RESET", 140, 3);
  }
    
// Draw a red frame while a button is touched

void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
  myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}


