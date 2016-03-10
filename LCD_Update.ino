void LCD_Update()
{
 
 //myGLCD.setFont (Ubuntu);
 //myGLCD.setFont (SmallFont);
  
  //Grafico bateria - Fill grafico
 if(valBatt >=12 && valBatt <12.1) {
   myGLCD.setColor(255,0 , 0);                      //vermelho
   myGLCD.fillRect(2, 22, 20, 41);}
 
 if(valBatt >=12.1 && valBatt <12.2) {
   myGLCD.setColor(255,0 , 0);                       //vermelho
   myGLCD.fillRect(2, 42, 20, 61);}
 
 if(valBatt >=12.2 && valBatt <12.3){
   myGLCD.setColor(255,0 , 0);                      //vermelho
   myGLCD.fillRect(2, 62, 20, 81);}
  
  if(valBatt >=12.3 && valBatt <12.4){
   myGLCD.setColor(255,255 , 0);                      //Amarelo
   myGLCD.fillRect(2, 82, 20, 100);}
  
  if(valBatt >=12.4 && valBatt <12.5){
   myGLCD.setColor(255,255 , 0);                      //Amarelo
   myGLCD.fillRect(2, 101, 20, 120);}
  
  if(valBatt >=12.5 && valBatt <12.6){
   myGLCD.setColor(255,255 , 0);                      //amarelo
   myGLCD.fillRect(2, 121, 20, 140);}
  
  if(valBatt >=12.6 && valBatt <12.7){
   myGLCD.setColor(0,255 , 0);                      //verde
   myGLCD.fillRect(2, 140, 20, 160);}
  
  if(valBatt >=12.7 && valBatt <12.8){
   myGLCD.setColor(0,255 , 0);                      //verde
   myGLCD.fillRect(2, 161, 20, 179);}
  
  if(valBatt >=12.8 && valBatt <13){
   myGLCD.setColor(0,255 , 0);                      //verde
   myGLCD.fillRect(2, 180, 20, 199);}
   
   if(valBatt >=13){
   myGLCD.setColor(0,255 , 0);
   myGLCD.fillRect(2, 200, 20, 219);}               //verde
   
 //Valor SUPERIOR e estado INFERIOR bateria
 myGLCD.setColor(255,255,255);
 myGLCD.setFont (Ubuntu);
 myGLCD.printNumI(valBatt, 48, 41);
 myGLCD.print("V", 41, 72);
 
 if(valBatt >= 12.6) {
   myGLCD.setColor(0, 255, 0);  
   myGLCD.print("GOOD", 1, 5); }
 
 if (valBatt <12.6) {
   myGLCD.setColor(255, 0, 0);
   myGLCD.print("CHARGE", 1, 5); }
 
 if(valBatt < 12) {
   myGLCD.setColor(0, 255, 0);  
   myGLCD.print("BAD", 1, 5); }
    
  //Grafico temp motor - Fill grafico
 if(sensorValue >=50 && sensorValue <60) {
   myGLCD.setColor(0,255 , 0);                      //verde
   myGLCD.fillRect(300, 22, 318, 41);
   myGLCD.setColor(0,0,255);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("COLD", 287, 5);}
 
 if(sensorValue >=60 && sensorValue <70) {
   myGLCD.setColor(0,255 , 0);                       //verde
   myGLCD.fillRect(300, 42, 318, 61);
   myGLCD.setColor(0,0,255);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("COLD", 287, 5);}
 
 if(sensorValue >=70 && sensorValue <80){
   myGLCD.setColor(0,255 , 0);                      //verde
   myGLCD.fillRect(300, 62, 318, 80);
   myGLCD.setColor(0,0,255);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("COLD", 287, 5);}
  
  if(sensorValue >=80 && sensorValue <90){
   myGLCD.setColor(0,255 , 0);                      //verde
   myGLCD.fillRect(300, 81, 318, 100);
    myGLCD.setColor(0,0,255);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("COLD", 287, 5);}
  
  if(sensorValue >=90 && sensorValue <95){
   myGLCD.setColor(0,255 , 0);                      //verde
   myGLCD.fillRect(300, 101, 318, 120);
   myGLCD.setColor(0,255,0);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("OK", 287, 5);}
  
  if(sensorValue >=95 && sensorValue <97){
   myGLCD.setColor(255,255 , 0);                      //amarelo
   myGLCD.fillRect(300, 121, 318, 140);
   myGLCD.setColor(0,255,0);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("OK", 287, 5);}
  
  if(sensorValue >=97 && sensorValue <99){
   myGLCD.setColor(255,255 , 0);                      //amarelo
   myGLCD.fillRect(300, 141, 318, 160);
   myGLCD.setColor(0,255,0);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("HOT", 287, 5);}
  
  if(sensorValue >=99 && sensorValue <100){
   myGLCD.setColor(255,255 , 0);                      //amarelo
   myGLCD.fillRect(300, 161, 318, 179);
   myGLCD.setColor(255,255,0);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("HOT", 287, 5);}
  
  if(sensorValue >=100 && sensorValue <105){
   myGLCD.setColor(255 ,0 , 0);                      //vermelho
   myGLCD.fillRect(300, 180, 318, 199);
   myGLCD.setColor(255,0,0);        
   myGLCD.setFont (SmallFont);
   myGLCD.print("HOT", 287, 5);}
   
   if(sensorValue >=105){
   myGLCD.setColor(255, 0, 0);
   myGLCD.fillRect(300, 200, 318, 218);
   myGLCD.setColor(255,0,0);
   myGLCD.setFont (SmallFont);
   myGLCD.print("STOP", 287, 5);}               //vermelho
   
   //Mostrador temp. engine
 myGLCD.setColor(255,255,255);
 myGLCD.setFont (Ubuntu);
 myGLCD.printNumI(sensorValue, 196, 41);
 myGLCD.print("C", 270, 41);

///--- Conta Kilometros
 myGLCD.setColor(255,255,255);
 myGLCD.setFont (Ubuntu);
 myGLCD.printNumI(kmh, 32, 165);
 
 ///--- Trip 
 myGLCD.setColor(255,255,255);
 myGLCD.setFont (Ubuntu);
 myGLCD.printNumI(f_TripA, 32, 165);
  
 ///--- grafico inclinacao
 
 
 
 ///---Graus inclinacao
 
 
 ///--- forca G 
 
 
  ///--- data
   myGLCD.setColor(126,188,209);
   myGLCD.setFont (SmallFont);
   myGLCD.printNumI(valDateDay, 69, 1);
   myGLCD.print("/", 77, 1);
   myGLCD.printNumI(valDateMonth, 79, 1);
   myGLCD.print("/", 87, 1);
   myGLCD.printNumI(valDateYear, 89, 1);
   
   
   /*
  Serial.print( valTimeHH, DEC );
  Serial.print(F( ":" ));
  Serial.print( valTimeMM, DEC );
  
  Serial.print(F( "  " ));
  Serial.print( valDateMonth, DEC );
  Serial.print(F( "/" ));
  Serial.print( valDateDay, DEC );
  Serial.print(F( "/" ));
  Serial.println( valDateYear, DEC );
  */
  
  ///---hora
   myGLCD.setColor(126,188,209);
   myGLCD.setFont (SmallFont);
   myGLCD.printNumI(valTimeHH, 196, 1);
   myGLCD.print(":", 204, 1);
   






}
