// Sensor values
int valMPH        = 0;              // Miles per hour, GPS: 0 to 100
long valODO       = 0L;             // Odometer in miles, internal: 0 to 999,999
int valTripA      = 0;              // Trip A miles, internal: 0 to 9,999
int valTripB      = 0;              // Trip B miles, internal: 0 to 9,999
int valTimeHH     = 0;              // Current time hours, RTC: 1 to 12
int valTimeMM     = 0;              // Current time minutes, RTC: 0 to 59
int valDateMonth  = 0;              // Current date month, RTC: 1 to 12
int valDateDay    = 0;              // Current date day, RTC: 1 to 31
int valDateYear   = 0;              // Current date year, RTC: 0 to 99
int valTemp       = 0;              // Temperature, TEMP: -255 to 255 (degrees F)
int valBatt       = 0;              // Battery level, BATT: 0 to 100 (percent)
int valBatt1      = 0;
int valLean       = 0;              // Lean amount, ACCEL: -90 to 90 (angle)
long valHeading   = 0L;             // Heading, GPS: 0 to 36000 (degrees)
float f_TripA = 0.0;
float f_TripB = 0.0;
float f_ODO = 0.0;

// LM35
float sensorValue;
float sensorValue1;
float sensorValue2;
float sensorValue3;
float sensorValue4;
float sensorValue5;
float sensorValue6;
float sensorValue7;
float sensorValue8;
float sensorValue9;
float sensorValue10;

//lcd 
int buf[318];
int x, x2;
int y, y2;
int r;

//lcd touch
char stCurrent[20]="";
int stCurrentLen=0;
char stLast[20]="";

//Speedometer
int reedVal;
long timer;                    // time between one full rotation (in ms)
float kmh;
float radius = 13.5;            // tire radius (in inches)
float circumference;
float Perimeter = 3.1416*(2*radius);
int maxReedCounter = 100;        //min time (in ms) of one rotation (for debouncing)
int reedCounter;

//Ignicion
int Val;





