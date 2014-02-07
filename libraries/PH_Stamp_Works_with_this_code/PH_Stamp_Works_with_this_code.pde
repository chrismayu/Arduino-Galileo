//PH - 14, 15 (Serial3)
//#define DEBUG
#include <LCDBV4512I2C.h>
#include <LiquidCrystal.h>
#include <WProgram.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ledTestPin 13
#define ledLightPin 10
#define tempSensorPin 5
#define relaisPin1 34
#define relaisPin2 35
#define relaisPin3 36
#define relaisPin4 37
#define buzzerPin 9
#define Main_Pump 22
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcdsmall(0x27,16,2); // set the LCD address to 0x27

// PH
const float pHMax = 6.90;
const float pHMin = 6.50;
const float pHMaxAlarm = 8.5;
const float pHMinAlarm = 5.5;
float pHCalibrationValue = -0.18; //11
float pHValue = 0.0;
float calPHValue = 0.0;
const int eeAddrPHCal = 5;
// ORP
const int eeAddrORPCal = 10;
// LED
byte minLuminousIntensity = 7;
const float ledOn1 = 7.50; // time in decimal format. z.B 7:20 = 7.33
const float ledOff1 = 11;
const float ledOn2 = 16.50;
const float ledOff2 = 20;
// clock variables
uint16_t startAddr = 0x0000;            // Start address to store in the NV-RAM
uint16_t lastAddr;                      // new address for storing in NV-RAM
uint16_t TimeIsSet = 0xaa55;            // Helper that time must not set again
// initialize the library with the numbers of the interface pins
//LiquidCrystal LCD(12, 11, 4, 5, 6, 7);
// PH and ORP stamp
int orpValue = 0;
// global variables
byte luminousIntensity = minLuminousIntensity;
byte curHour;
byte oldHour;
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(tempSensorPin);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
// arrays to hold device address
DeviceAddress insideThermometer;
float tempC;
// EEPROM
//I2C_eeprom EE(0x50);
const unsigned long EEPROM_SIZE = 65536;      // 24LC512 64K bytes
unsigned long eeAddr = 0;
const int eeAddrCounter = 0;
const byte blockLen = 13;


void setup() {


Serial.begin(9600);
  // pH stamp
  Serial3.begin(38400);
  Serial3.print("L1");
  Serial3.print(13, BYTE);
 // pHCalibrationValue = eepromReadFloat(eeAddrPHCal);
   Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC); 
  Serial.println();
  
  
  
   lcdsmall.init(); // initialize the lcd
  lcdsmall.backlight();
  // Print a message to the LCD.                                 



  lcdsmall.setCursor(0, 0);
  lcdsmall.print("I am starting up");
    pinMode(Main_Pump, OUTPUT);
    digitalWrite(Main_Pump, LOW);
  
}


void loop() {
  
   printPH();
 
 

 

}
void printTemperature(DeviceAddress deviceAddress)
{
  // method 1 - slower
  //Serial.print("Temp C: ");
  //Serial.print(sensors.getTempC(deviceAddress));
  //Serial.print(" Temp F: ");
  //Serial.print(sensors.getTempF(deviceAddress)); // Makes a second call to getTempC and then converts to Fahrenheit

  // method 2 - faster
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void printPH()
{
  // ph stamp a new command
printTemperature(insideThermometer);
 // float tempC = sensors.getTempC(deviceAddress);
  if(tempC > 0)
  {
    // temperatur sensor nicht angeschlossen
    Serial3.print(tempC, DEC);  // send temperatur or "r". nicht beides!
    Serial3.print(13, BYTE); // ende
  }
  else
  {
    Serial3.print("r");  // send temperatur or "r". nicht beides!
    Serial3.print(13, BYTE); // ende
  }
  delay(550);

 // LCD.setCursor(0, 1);
//  LCD.print("PH ");
  byte holding=Serial3.available();            //lets read how many bytes have been received

  Serial.print(holding);
  Serial.println(" byte received from PH stamp");


  if(holding > 4 && holding <=12) {  //if we see the more than three bytes have been received by the Arduino
    char data[12];          //this is where the data from the stamp is stored. if no pH probe is connected, the message "check probe" is transmitted.
    for(byte i=0; i <= holding-1;i++) {  //we make a loop that will read each byte we received
      data[i]= char(Serial3.read());     //and load that byte into the stamp_data array
    }

    Serial.print("PH=");
    for(byte i=0; i <= holding-1;i++) {  //we now loop through the array
      Serial.print(data[i]);             //printing each byte we received  through the hardware UART
    }
    Serial.println(""); 

    if (atoi(data) != 0) {
      pHValue = atof(data);
    }
    else {
      pHValue = 0;}

    if(pHValue > 0) {
    
    calPHValue = pHValue + pHCalibrationValue;
    lcdsmall.clear();
        Serial.println("Updated PH valve  *******************************************");
    lcdsmall.setCursor(0, 1);
     lcdsmall.print("Final PH:");
     lcdsmall.println(calPHValue);
    
    
    lcdsmall.setCursor(0, 0);
     lcdsmall.print("Probe:");
     lcdsmall.println(pHValue);
   
   
    Serial.print("calPHValue:");
    Serial.println(calPHValue);
     Serial.print("pHCalibrationValue:");
    Serial.println(pHCalibrationValue);
    Serial.print("PHValue:");
    Serial.println(pHValue);
 
    }else{}
  }
  else if(holding == 0)
  {
    Serial.println("Error: No data from PH probe");
  }
  else if(holding > 12)
  {
    Serial.println("Error: Too many data from PH probe. Max 12 is allowed.");
  }
  if(pHValue > 0.0 )
  {
    // Alarm beim PH Sensor
    if(calPHValue <= pHMinAlarm || calPHValue >= pHMaxAlarm)
    {
    //  Alarm("Check PH Value");
    }
    else
     // ClearAlarmMessage();

    // CO2 einschalten oder ausschalten
    if(pHValue >= pHMax) {
#ifdef DEBUG
      Serial << "PH >= " << pHMax << endl;
#endif
      digitalWrite(relaisPin1, LOW); // LOW ist einschlten!
    }
    else if(pHValue <= pHMin) {
#ifdef DEBUG
      Serial << "PH <= " << pHMin << endl;
#endif
      digitalWrite(relaisPin1, HIGH); // HIGH ist ausschlten!
    }
    else
      digitalWrite(relaisPin1, HIGH);
  }

 int PH_first = calPHValue; ////  makes 26.7 into 26
      int    PH2a = calPHValue * 100;////  makes 26.7 into 2670
        int PH3a = PH_first * 100; /// makes 26 into 2600
         int  PH_second = PH2a - PH3a;
         
          int PH_firsta = PH_second; ////  makes 26.7 into 26
      int    PH2b = PH_second * 10;////  makes 26.7 into 2670
        int PH3b = PH_first * 10; /// makes 26 into 2600
         int  PH_third = PH2a - PH3a;
         
         
         int wholeTempC = calPHValue; // The whole part
int fracTempC = (calPHValue - wholeTempC) * 100; // The fractional part * 1000 

         

        char tempdata[20];
        sprintf (tempdata, "The PH is: %d.%.2d", PH_first, PH_second); 
       // sprintf (tempdata, "The PH is: %d", calPHValue);
        Serial.println(tempdata);
        
        char tempdata2[20];
        sprintf (tempdata2, "The PH is: %d.%2d", wholeTempC, fracTempC); 
        Serial.println(tempdata2);

  Serial3.flush();
}

 
 
  

