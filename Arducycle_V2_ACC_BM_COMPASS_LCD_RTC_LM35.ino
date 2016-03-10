/**************************** 
 ARDUCYCLE
 Logic / Sensor Module - Arduino
  
 Created April 13, 2014
 Rev 1.0
 Vasco Pereira
 *****************************/
#include <UTFT.h>
#include <UTouch.h>
#include <Timer.h>
#include "Timer.h"
#include <Wire.h>
#include <RTClib.h>                                      // Credit: Adafruit, library do RTC
#include <TimedAction.h>
#include <HMC5883L.h>
#include "Config.h"

// Initialize display
// ------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Uno/2009 Shield            : <display model>,19,18,17,16
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Due       : <display model>,25,26,27,28
// Teensy 3.x TFT Test Board                   : <display model>,23,22, 3, 4
// ElecHouse TFT LCD/SD Shield for Arduino Due : <display model>,22,23,31,33
//
// Uncomment the next line for Arduino Mega
UTFT myGLCD(ITDB32S,38,39,40,41);   // Remember to change the model parameter to suit your display module!

// Initialize touchscreen
// ----------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Uno/2009 Shield            : 15,10,14, 9, 8
// Standard Arduino Mega/Due shield            :  6, 5, 4, 3, 2
// CTE TFT LCD/SD Shield for Arduino Due       :  6, 5, 4, 3, 2
// Teensy 3.x TFT Test Board                   : 26,31,27,28,29
// ElecHouse TFT LCD/SD Shield for Arduino Due : 25,26,27,29,30
//
UTouch  myTouch( 6, 5, 4, 3, 2);

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Ubuntu[9124];

// Uncomment the defs to send values to Serial for debug
//#define DEBUG_ACCEL
//#define DEBUG_TEMP
//#define DEBUG_BATTMON
//#define DEBUG_RTC
//#define DEBUG_BUZZER
//#define DEBUG_COMPASS
//#define DEBUG_Speed
//#define DEBUG_HALL

// Analog pin assignments
#define ACCEL_X_PIN   A0            // Accelerometer ADXL-320 X axis
#define ACCEL_Y_PIN   A1            // Accelerometer ADXL-320 Y axis
#define ACCEL_Z_PIN   A2
#define BATT_PIN      A3            // Battery Monitor level
#define LM35_PIN      A4            // Temp Sensor
#define reed          A5             //pin connected to read switch spedd

// Digital pin assignments
#define BUZZ_PIN          7            // Buzzer 2.048Khz
#define RL1BattChargePin  28        // power Output to Carregador de bateria
#define IGNICION          10          // Power check from iginition

// RTC non-volatile storage
#define RTC_I2C_ADDR  0x68         // Real time clock address on the I2C bus
#define RAM_ADDR      8            // RTC RAM registers start at address 8
#define TRIPA_ADDR    RAM_ADDR     // Trips, ODO, lat and long are all floats, 4 bytes ea.     
#define ODO_ADDR      TRIPB_ADDR + 4

#define NOFIELD 505L    // Analog output with no applied field, calibrate this for Speed

// Uncomment one of the lines below according to device in use A1301 or A1302
// This is used to convert the analog voltage reading to milliGauss
//#define TOMILLIGAUSS 1953L  // For A1301: 2.5mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 1953mG
#define TOMILLIGAUSS 3756L  // For A1302: 1.3mV = 1Gauss, and 1024 analog steps = 5V, so 1 step = 3756mG//// #define TOMILLIGAUSS 1.953125

// InicializaÃ§Ã£o Bussola
HMC5883L compass;

// Record any errors that may occur in the compass.
int error = 0;

//--- Inicializacao do RTC
RTC_DS1307 RTC;

/************************************************ RTC - Definicao Chars **********************************************************************/
const int DS1307 = 0x68; // Address of DS1307 see data sheets
const char* days[] =
{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* months[] =
{"January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December"};
 
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;

//this initializes a TimedAction object.
//Put here all Tasks
TimedAction BATTMON_UpdateAction = TimedAction (60000, BATTMON_Update);
TimedAction TEMP_UpdateAction = TimedAction (5000, TEMP_Update);
TimedAction MAGAction = TimedAction (1000, MAG);
TimedAction SpeedAction = TimedAction (45, Speed);
TimedAction ACCEL_UpdateAction = TimedAction (35, ACCEL_Update);
TimedAction LCD_UpdateAction = TimedAction (25, LCD_Update);
TimedAction Button_ClickAction = TimedAction (15, Button_Click);
TimedAction IgnicionAction = TimedAction ( 50, Ignicion);
TimedAction BattChargeAction = TimedAction (3600000, BattCharge);      //check every hour

// VOID SETUP
void setup() {
  
  pinMode( BUZZ_PIN, OUTPUT );
  randomSeed(analogRead(5));
  Serial.begin (9600);                  
   
 // Inicializacao do RTC
  Wire.begin();
  RTC.begin();
  DateTime now = RTC.now();
  
  // Setup the LCD
  myGLCD.InitLCD();
  myTouch.InitTouch();
  myGLCD.clrScr();
  myTouch.setPrecision(PREC_HI);
  //myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(0, 0, 0);
  
  compass = HMC5883L(); // Construct a new HMC5883 compass.
  
  TEMP_UpdateAction.enable();
  ACCEL_UpdateAction.enable();
  BATTMON_UpdateAction.enable();
  Button_ClickAction.enable();
  LCD_UpdateAction.enable();
  MAGAction.enable();
  SpeedAction.enable();  
  IgnicionAction.enable();
  BattChargeAction.enable();
  
  error = compass.SetScale(1.3); // Set the scale of the compass.
  if(error != 0) // If there is an error, print it out.
  Serial.println(compass.GetErrorText(error));
    
  error = compass.SetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) // If there is an error, print it out.
  Serial.println(compass.GetErrorText(error));
  
     
/**************************************************** DESMARCAR PARA ACERTAR A HORA *********************************************************/
  // Acertar_Hora();
/**************************************************************************************************************************************************/
      
  // DEFINITION analog pins
  pinMode(ACCEL_X_PIN,INPUT);
  pinMode(ACCEL_Y_PIN,INPUT);
  pinMode(BATT_PIN,INPUT);
  pinMode(LM35_PIN,INPUT);
  pinMode(reed, INPUT);

  // DEFINITION digital pins
  pinMode(BUZZ_PIN,OUTPUT);
  pinMode(RL1BattChargePin,OUTPUT);
  pinMode(IGNICION,INPUT);
 
  //  Read trip, ODO, and location data from RTC storage to init vals
  f_TripA = RTC_ReadFloat( TRIPA_ADDR );
     
  BUZZ_Play();        // Signal setup complete
  
  // Serial comm to PC if any debug defs exist
  #if defined DEBUG_ACCEL || defined DEBUG_TEMP || defined DEBUG_BATTMON || defined DEBUG_RTC || defined DEBUG_BUZZER ||defined DEBUG_Speed
  Serial.println( "Debug enabled..." );
  #define DEBUG
  #endif
  
  LCD_boot();
  //---- ------- DRAW PANEL
  myGLCD.clrScr();
 myGLCD.setBackColor(0, 0, 0);                      //preto
 
 ///--- Grafico bateria - Rectangulo
 myGLCD.setColor(255, 255, 255);                    //branco 
 myGLCD.drawRect(1, 21, 21, 220);  //10 quadrados de 20 larg por 20 alt
 
 //--- DISPLAY BATERIA
 myGLCD.setColor(126,188,209);
 myGLCD.setFont (SmallFont);
 myGLCD.print("Bat.V.", 1, 224);
 
//--- Grafico temp motor
 myGLCD.setColor(255, 255, 255);                    //branco 
 myGLCD.drawRect(299, 21, 319, 219);                    //10 quadrados de 20 larg por 20 alt

//--- DISPLAY TEMP. MOTOR
 myGLCD.setFont (SmallFont);
 myGLCD.setColor(126,188,209);
 myGLCD.print("Eng.", 300, 15);
 
 //--- DISPALY VELOCIDADE
  myGLCD.print("Km/h", 146, 165);
  
 //--- DISPLAY TRIP
 myGLCD.print("Km", 146, 110);

 ///--- grafico inclinacao
 
 
 
 ///---Graus inclinacao
 
 
 ///--- forca G 

 
  
  drawButtons(); 
}

//************************
// VOID LOOP
void loop( ) {
  
 //Start all tasks here
 // Get updates from the sensors
 
 BattChargeAction.check();  
 IgnicionAction.check();
  
  TEMP_UpdateAction.check();                         // Get initial temperature reading 
  ACCEL_UpdateAction.check();
  Button_ClickAction.check();
  LCD_UpdateAction.check();
  MAGAction.check();
  SpeedAction.check();
  IgnicionAction.check();
  BATTMON_UpdateAction.check();}
  
//**************************
// RTC DS1307
// Utility functions

// Convert decimal to BCD and BCD to decimal
byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}

//**************************
// RTC DS1307
// RAM register access functions
//

// Reads a 2-byte integer value from the RTC RAM registers
int RTC_ReadInteger( int valAddr )
{
  // Set the register pointer
  Wire.beginTransmission( RTC_I2C_ADDR );
  Wire.write( valAddr );
  Wire.endTransmission( );

  // Read 2 bytes into int value
  Wire.requestFrom( RTC_I2C_ADDR, 2 );
  int value =  Wire.read( );
  value = ( value << 8 ) +  Wire.read( );
  
  return value;
}

// Reads a 4-byte float value from the RTC RAM registers
float RTC_ReadFloat( int valAddr )
{
  float value;
  byte  *byteArray = (byte *) &value;
  
  // Set the register pointer
  Wire.beginTransmission( RTC_I2C_ADDR );
  Wire.write( valAddr );
  Wire.endTransmission();

  // Read 4 bytes can convert to float value
  Wire.requestFrom( RTC_I2C_ADDR, 4 );
  byteArray[3] =  Wire.read( );
  byteArray[2] =  Wire.read( );
  byteArray[1] =  Wire.read( );
  byteArray[0] =  Wire.read( );
  
  return value;
}

// Writes a 2-byte integer value to the RTC RAM registers
void RTC_WriteInteger( int valAddr, int value )
{
  if( valAddr > 7 && valAddr  < 63 )  // Don't let writes go to the RTC registers 0 - 7
  {
    Wire.beginTransmission( RTC_I2C_ADDR );
     Wire.write( valAddr );

    // Write high byte, low byte
     Wire.write( ( unsigned char )( value >> 8 ) );
     Wire.write( ( unsigned char )value ); 
    
    Wire.endTransmission( );
  }  
}

// Writes a 4-byte float value to the RTC RAM registers
void RTC_WriteFloat( int valAddr, float value )
{
  if( valAddr > 7 && valAddr  < 61 )  // Don't let writes go to the RTC registers 0 - 7
  {
    Wire.beginTransmission( RTC_I2C_ADDR );
     Wire.write( valAddr );
    
    // Write high word (high byte/low byte), low word (high byte/low byte)
    byte  *byteArray;
    byteArray = (byte *) &value;
     Wire.write( byteArray[3] );
     Wire.write( byteArray[2] );
     Wire.write( byteArray[1] );
     Wire.write( byteArray[0] );

    Wire.endTransmission( );
  }
 } 

/******************************************************************************************************************************************/
void setTime() {
 
  Serial.print("Please enter the current year, 00-99. - ");
  year = readByte();
  Serial.println(year);
  Serial.print("Please enter the current month, 1-12. - ");
  month = readByte();
  Serial.println(months[month-1]);
  Serial.print("Please enter the current day of the month, 1-31. - ");
  monthday = readByte();
  Serial.println(monthday);
  Serial.println("Please enter the current day of the week, 1-7.");
  Serial.print("1 Sun | 2 Mon | 3 Tues | 4 Weds | 5 Thu | 6 Fri | 7 Sat - ");
  weekday = readByte();
  Serial.println(days[weekday-1]);
  Serial.print("Please enter the current hour in 24hr format, 0-23. - ");
  hour = readByte();
  Serial.println(hour);
  Serial.print("Please enter the current minute, 0-59. - ");
  minute = readByte();
  Serial.println(minute);
  second = 0;
  Serial.println("The data has been entered.");
 
  // The following codes transmits the data to the RTC
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekday));
  Wire.write(decToBcd(monthday));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(byte(0));
  Wire.endTransmission();
  // Ends transmission of data
}

byte readByte() {
  while (!Serial.available()) delay(10);
  byte reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n') {
    if (incomingByte >= '0' && incomingByte <= '9')
      reading = reading * 10 + (incomingByte - '0');
    else;
    incomingByte = Serial.read();
  }
  Serial.flush();
  return reading;
}

/******************************************************************************************************************************************/
void printTime() {
  char buffer[3];
  readTime();
  Serial.print(days[weekday-1]);
  Serial.print(" ");
  Serial.print(months[month-1]);
  Serial.print(" ");
  Serial.print(monthday);
  Serial.print(", 20");
  Serial.print(year);
  Serial.print(" ");
  /*if (hour > 12) {
    hour -= 12;
    AMPM = " PM";
  }
  else AMPM = " AM";*/
  Serial.print(hour);
  Serial.print(":");
  sprintf(buffer, "%02d", minute);
  Serial.print(buffer);
  //Serial.println(AMPM);
}

/*****************************************************************************************************************************************/
void readTime() {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}

/************************************************************************************************************************************************/

/* Output the data down the serial port.
void Output(MagnetometerRaw raw, MagnetometerScaled scaled, float heading, float headingDegrees)
{
   Serial.print("Raw:\t");
   Serial.print(raw.XAxis);
   Serial.print("   ");   
   Serial.print(raw.YAxis);
   Serial.print("   ");   
   Serial.print(raw.ZAxis);
   Serial.print("   \tScaled:\t");
   
   Serial.print(scaled.XAxis);
   Serial.print("   ");   
   Serial.print(scaled.YAxis);
   Serial.print("   ");   
   Serial.print(scaled.ZAxis);

   Serial.print("   \tHeading:\t");
   Serial.print(heading);
   Serial.print(" Radians   \t");
   Serial.print(headingDegrees);
   Serial.println(" Degrees   \t");
   
   
}
*/
  
  

