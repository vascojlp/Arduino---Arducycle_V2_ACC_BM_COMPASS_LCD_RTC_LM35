// http://playground.arduino.cc/Code/HallEffect
// http://playground.arduino.cc/Main/ReadingRPM
// http://www.instructables.com/id/Arduino-Bike-Speedometer/

void Speed()
{

  /*
  // measure magnetic field
  int raw = analogRead(0);   // Range : 0..1024



  long compensated = raw - NOFIELD;                 // adjust relative to no applied field 
  long gauss = compensated * TOMILLIGAUSS / 1000;   // adjust scale to Gauss
 */ 
 
//calculations
//tire radius ~ 13.5 inches
//circumference = pi*2*r =~85 inches
//max speed of 35mph =~ 616inches/second
//max rps =~7.25kmh

// TIMER SETUP- the timer interrupt allows precise timed measurements of the reed switch
  //for more info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1

  reedVal = digitalRead(reed);        //get val of A0
  
  if (reedVal){                        //if reed switch is closed
    if (reedCounter == 0){              //min time between pulses has passed
     kmh = (56.8*float(circumference))/float(timer);          //calculate miles per hour
      timer = 0;                              //reset timer
    }
    else{
      if (reedCounter > 0){              //don't let reedCounter go negative
        reedCounter -= 1;                //decrement reedCounter
      }
    }
  }
  else{                            //if reed switch is open
    if (reedCounter > 0){              //don't let reedCounter go negative
      reedCounter -= 1;                //decrement reedCounter
    }
  }
  if (timer > 2000){
    kmh = 0;//if no new pulses from reed switch- tire is still, set kmh to 0
  }
  else{
    timer += 1;//increment timer
  }

///--- Trip

volatile int clickCount = 0;    // The sensor click counter
int saveClickCount = reedVal;

  if( clickCount != saveClickCount )
  {
    #ifdef DEBUG_HALL
    Serial.println( );
    Serial.println( clickCount );
    #endif
    saveClickCount = clickCount;
  }  
 
  clickCount++;

float trip = clickCount * Perimeter ;
          
          if( trip >= 0.001 )      // Accumulate every 25th of a mile
          {
            f_TripA += trip; 
            RTC_WriteFloat( TRIPA_ADDR, f_TripA );
          }
                      
            if( f_TripA >= 9999 ){    // Reset trip meters after 9999 miles
              f_TripA = 0.0f; }

 #ifdef DEBUG_Speed
 Serial.print("Raw reading: ");
 Serial.println(raw);
 Serial.print(" Gauss ");
 Serial.print(gauss);
 
 if (gauss > 0)     Serial.println("(South pole)");
 else if(gauss < 0) Serial.println("(North pole)");
 else               Serial.println();
  Serial.print(" Km/h ");
  Serial.println(kmh);
  Serial.print(" Trip ");
  Serial.println(trip);
  Serial.print(" Clicks ");
  Serial.print(clickCount);
 #endif
 
}



