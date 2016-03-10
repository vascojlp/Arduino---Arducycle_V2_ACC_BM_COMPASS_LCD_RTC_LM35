void BattCharge() {
  
  // Battery Monitor
//CALIBRAR VALORES DA BATERIA - 604= DISCHARGED0% -  870 cHARGED 100%
//0v a 5v --> 0 a 14v --> 0 a 1024, logo valBattl = (battLevell *14)/1024

  int battLevel1 = analogRead( BATT_PIN );
  
  //valBatt1 = map( battLevel1, 604, 870, 0, 100 );
  valBatt1 = (battLevel1*14)/1024;
  
  if(valBatt1 <= 12.8) {
    digitalWrite(RL1BattChargePin, LOW);}
  if (valBatt1 >= 13,5) {
    digitalWrite(RL1BattChargePin, HIGH);} 
      
  

  }

