//************************
// Temperature LM35

void TEMP_Update( )
{
 sensorValue1 = analogRead(LM35_PIN);   //reads voltage on Pin A0
   sensorValue2 = analogRead(LM35_PIN);  
    sensorValue3 = analogRead(LM35_PIN);  
     sensorValue4 = analogRead(LM35_PIN);  
      sensorValue5 = analogRead(LM35_PIN);  
       sensorValue6 = analogRead(LM35_PIN);  
        sensorValue7 = analogRead(LM35_PIN);  
         sensorValue8 = analogRead(LM35_PIN);  
          sensorValue9 = analogRead(LM35_PIN);  
           sensorValue10 = analogRead(LM35_PIN);  
           
  sensorValue = (sensorValue1+sensorValue2+sensorValue3+sensorValue4+sensorValue5+sensorValue6+sensorValue7+sensorValue8+sensorValue9+sensorValue10)/10;
  
  #ifdef DEBUG_TEMP
  Serial.print(F( "valTemp = " ));
  Serial.println(sensorValue, DEC);
  #endif

}


