//************************
// BUZZER 2.048Khz
//
void BUZZ_Play( )
{
  for ( int i = 0; i < 1048; i++ )
  {
    // 1 / 2048Hz = 488uS, or 244uS high and 244uS low to create 50% duty cycle
    digitalWrite( BUZZ_PIN, HIGH );
    delayMicroseconds( 244 );
    digitalWrite( BUZZ_PIN, LOW );
    delayMicroseconds( 244 );
  } 
}

