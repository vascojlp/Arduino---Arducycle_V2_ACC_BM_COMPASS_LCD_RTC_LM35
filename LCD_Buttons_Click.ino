void Button_Click()
{
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      
      if ((y>=1) && (y<=30))  
      {
        if ((x>=135) && (x<=185))  // Button: 1
        {
          waitForIt(136, 2, 184, 29);
          f_TripA =0;
          RTC_WriteFloat( TRIPA_ADDR, f_TripA );
         
          }
        }
      }
      }
      }


