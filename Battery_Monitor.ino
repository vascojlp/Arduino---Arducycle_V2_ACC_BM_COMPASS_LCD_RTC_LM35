//************************
// Battery Monitor
//CALIBRAR VALORES DA BATERIA - 604= DISCHARGED0% -  870 cHARGED 100%

void BATTMON_Update( )
{
  int battLevel = analogRead( BATT_PIN );
  
  //valBatt = map( battLevel, 604, 870, 0, 100 );
  valBatt = (battLevel*14)/1024;
  
  #ifdef DEBUG_BATTMON
  Serial.print(F( "BATT = "));
  Serial.print( battLevel, DEC );
  Serial.print(F( " " ));
  Serial.print(F( "valBatt = " ));
  Serial.println( valBatt, DEC );
  #endif
}


