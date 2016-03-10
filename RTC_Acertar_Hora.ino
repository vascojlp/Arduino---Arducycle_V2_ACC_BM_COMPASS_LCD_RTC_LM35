void Acertar_Hora()
{

//**************************
// RTC DS1307
// Debuguing 
  #ifdef DEBUG_RTC
  Serial.print( hour, DEC );
  Serial.print(F( ":" ));
  Serial.print( minute, DEC );
  Serial.print(F( ":" ));
  Serial.print( second, DEC );
  Serial.print(F( "  " ));
  Serial.print( month, DEC );
  Serial.print(F( "/" ));
  Serial.print( dayOfMonth, DEC );
  Serial.print(F( "/" ));
  Serial.print( year, DEC );
  Serial.print(F( "  Day_of_week:" ));
  Serial.println( dayOfWeek, DEC );
  
  Serial.print( valTimeHH, DEC );
  Serial.print(F( ":" ));
  Serial.print( valTimeMM, DEC );
  Serial.print(F( "  " ));
  Serial.print( valDateMonth, DEC );
  Serial.print(F( "/" ));
  Serial.print( valDateDay, DEC );
  Serial.print(F( "/" ));
  Serial.println( valDateYear, DEC );
  #endif



// Set the time and date
  Serial.print(F("A DATA E HORA ACTUAL E: "));
  printTime();
  Serial.print(F("\n"));
  Serial.println(F("QUER ACTUALIZAR A DATA E HORA? Y/N"));
 
  while (!Serial.available()) delay(10);
  if (Serial.read() == 'y' || Serial.read() == 'Y')  {
    
    Serial.read();
    setTime();
    Serial.print(F("A DATA FOI ACTUALIZADA PARA: "));
    printTime();
  }
 
 Serial.print(F("\n"));
 Serial.println(F("O PROGRAMA VAI CONTINUAR..."));
 Serial.print(F("\n"));
 Serial.print(F("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"));
 Serial.print(F("\n"));
 Serial.print(F("  \n"));



}

