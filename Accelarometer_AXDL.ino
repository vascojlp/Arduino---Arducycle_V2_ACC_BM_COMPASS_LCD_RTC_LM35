//************************
// Accelerometer AXDL-...
//ATENÃ‡ÃƒO, LIGAR SENSOR A 3.3V 
// http://chionophilous.wordpress.com/2011/08/26/accelerometer-calibration-ii-simple-methods/
// http://bildr.org/2011/04/sensing-orientation-with-the-adxl335-arduino/
// http://www.instructables.com/id/Interfacing-ADXL335-with-ARDUINO/?ALLSTEPS
void ACCEL_Update( )
{
  
  //Make sure the analog-to-digital converter takes its reference voltage from
  // the AREF pin
  analogReference(EXTERNAL);
  
  float accelX = analogRead( ACCEL_X_PIN );
  float accelY = analogRead( ACCEL_Y_PIN );
  float accelZ = analogRead( ACCEL_Z_PIN );
  
  valLean = map( accelY, 0, 1023, 0, 255 );
  delay(2);
  
  //zero_G is the reading we expect from the sensor when it detects
  //no acceleration.  Subtract this value from the sensor reading to
  //get a shifted sensor reading.
  // Our 1G reading for the Z axis was 618, the -1G reading (upside down) was 413.  Linear interpolation (aka common sense)  tells us that 0G on the z-axis should be exactly in the middle: (618+413)/2 = 515.5 for Z
  float zero_G_x = 509.5;
  float zero_G_y = 502.5;
  float zero_G_z = 515.5;

  //scale is the number of units we expect the sensor reading to
  //change when the acceleration along an axis changes by 1G.
  //Divide the shifted sensor reading by scale to get acceleration in Gs.
  //We can also estimate the sensitivity-Scale. The difference between our two measurements should be 2G, so just find the difference and divide by 2: (618-413)/2 = 102.5 for Z
  float scale_x = 104.5;
  float scale_y = 105.5;
  float scale_z = 102.5;
  
  // ForÃ§as GÂ´s nos 3 eixos
  float Gx = (accelX - zero_G_x)/scale_x;
  float Gy = (accelY - zero_G_y)/scale_y;
  float Gz = (accelZ - zero_G_z)/scale_z;
  
  float G = (1+(Gx + Gy + Gz))/3;
 
  // InclinaÃ§Ã£o em graus
  //convert read values to degrees -90 to 90 - Needed for atan2 
  // The highest value I read from the sensor when it was standing still was 402, so that is 1g, and the lowest was 265, so that is 0g. Do this for X
  int minVal = 265;
  int maxVal = 402;

  int xAng = map(accelX, minVal, maxVal, -90, 90);
  //float yAng = map(accelY, minVal, maxVal, -90, 90);
  //float zAng = map(accelZ, minVal, maxVal, -90, 90);
  
  
  #ifdef DEBUG_ACCEL
  Serial.print(F( "ACCEL ADC X = "));
  Serial.print( accelX, DEC );
  Serial.print(F( ", " ));
  Serial.print(F( "ACCEL ADC Y = "));
  Serial.print( accelY, DEC );
  Serial.print(F( " , " ));
  
  Serial.print(F( "valLean = " ));
  Serial.println( valLean, DEC );
  Serial.print(F( "ACCEL Gx = "));
  
  Serial.print( Gx, DEC );
  Serial.print(F( ", " ));
  Serial.print(F( "ACCEL Gy = "));
  Serial.print( Gy, DEC );
  Serial.print(F( ", " ));
  Serial.print(F( "ACCEL Gz = "));
  Serial.print( Gz, DEC );
  Serial.print(F( ", " ));
  
  Serial.print(F( "Degrees XAng = "));
  Serial.print( xAng, DEC );
  Serial.print(F( ", " ));  
  #endif
}


