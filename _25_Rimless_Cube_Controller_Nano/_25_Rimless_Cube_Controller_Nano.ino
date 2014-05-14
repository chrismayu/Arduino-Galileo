
/*

 addd:
 clear screen before checking for enet and print that on screem ( that you are chekcing for it)
 
 when reset pushed - clear all fault and clear W/C and feeding, ato  ( also displkay on whole screen clearing it first
 
 Chris' Arduino Reef Controller
 
 cwcw
 ---------  Analog  ------------
 
 
 Analog Pin 0 = 
 Analog Pin 1 = 
 Analog Pin 2 = //LCD POT Sensor
 
 to be used :
 Pin 0 = RX
 Pin 1 = TX
 Pin 2 = Alarm
 Pin 3 = 
 Pin 4 = buzzerPin
 Pin 5 = MainPanelTempSensorPin 
 Pin 6 = AmbientTempSenserPin
 Pin 7 = TankTempSensorPin
 Pin 8 = ChillerTempSensorPin
 Pin 9 = MainPanelTempSensorPin,LightingPanelTempSensorPin,LightHeatSinkTempSensorPin,RefugeLightTempSensorPin 
 Pin 10 = WhiteledLightPin
 Pin 11 = BlueledLightPin
 Pin 12 = MixedledLightPinwsWS
 Pin 13 = Onboard LED
 
 Current:
 ---------  PWM  ------------
 Pin 0 = RX
 Pin 1 = TX
 Pin 2 = Alarm
 Pin 3 = TankTempSensorPin
 Pin 4 = buzzerPin
 Pin 5 = MainPanelTempSensorPin 
 Pin 6 = RefugeLightTempSensorPin
 Pin 7 = LightHeatSinkTempSensorPin
 Pin 8 = LightingPanelTempSensorPin
 Pin 9 =  
 Pin 10 = WhiteledLightPin
 Pin 11 = BlueledLightPin
 Pin 12 = MixedledLightPin
 Pin 13 = Onboard LED
 
 ---------  Digital  ------------
 Pin 18 = Serial - PH Stamp RX 
 Pin 19 = Serial - PH Stamp TX 
 Pin 20 = SDA for I2C
 Pin 21 = SCL for I2C
 -----
 Pin 42 = //LCD - Edge PB
 Pin 41 = //LCD - Center PB
 -Pin 25 = ATO_High
 -Pin 26 = ATO_Low
 -Pin 27 = ATO_Valve
 Pin 40 = //LCD - IF Remote Sensor
 Pin 45 = mode100pb
 Pin 44 = mode101pb
 Pin 43 = mode102pb
 Pin 47 = mode103pb
 Pin 50 = mode104pb - not used
 
 
 Pin 39 = Float Sensor for ATO
 Pin 38 = GFCI Input Monitoring
 
 
 Pin 22 = Bottom Relay # 2  = Omron Relay #2  - Main Pump
 Pin 23 = Bottom Relay # 1  = Omron Relay #1  - Heater
 Pin 24 = Bottom Relay # 4  = Omron Relay #4  - Chiller/ Fan
 Pin 25 = Bottom Relay # 3  = Omron Relay #3  - PowerHead
 Pin 26 = Bottom Relay # 6  = Omron Relay #6  - ATS Pump
 Pin 27 = Bottom Relay # 5  = Omron Relay #5  - Main lights
 Pin 28 = Bottom Relay # 8 - ATO Valve
 Pin 29 = Bottom Relay # 7 
 
 
 Pin 37 = Top Relay # 7
 Pin 36 = Top Relay # 8 
 Pin 35 = Top Relay # 5 
 Pin 34 = Top Relay # 6 
 Pin 33 = Top Relay # 3  
 Pin 32 = Top Relay # 4  - ATO Valve
 Pin 31 = Top Relay # 1 - ATS PUMP
 Pin 20 = Top Relay # 2 - Refuge LIghts
 
 //38 - gfci
 //39 - spare on termial block - ATO Float sensor
 // 47 feeding -  orange wire  103
 ///45 - ATO   100
 // 44 - water change  101
 // 43 reset 102
 //   
 // 42 -  //LCD Right PB
 // 41 -  //LCD centerPB
 // 40 -  IR
 
 // bottom
 //1 = Skimmer
 //2 =  ATO Pump
 //3 =  Power head
 //4 =   Reactor
 //5 =  Main Pump
 //6 =  Heater
 //7 =  Grounding Plug
 //8 =  Spare Rec - used for Jebco powerhead
 
 // top
 //1 = Refuge Lights 
 //2 = Shelf Light
 //3 =  
 //4 =  
 //5 =  
 //6 =  
 //7 =  
 //8 =  
 
 
 */

 
//#include <LiquidCrystal.h>
#include <WProgram.h>
#include <Wire.h>
#include <DS1307new.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//#include <EtherCard.h> 
 
//#include <Streaming.h>
//#include <SPI.h>
//#include <Ethernet.h>
#include "PCF8574.h" // Required for PCF8575

#define redchip 0x24 // Used on the Top Relays 
#define yellowchip 0x21 // for Push Buttons
#define greenchip 0x20 // Used on the Bottoms Relays

/** PCF8575 instance */
PCF8574 top_relays;
PCF8574 bottom_relays;
//PCF8574 buttons;

#define ROWS 4
#define COLS 4

#define PCF8574_ADDR 0x38
 

 
//#define DEBUG
//#define DEBUG_EEPROM

#define DEBUG 1

#define SHARE_FEED_ID 38028 // this is your heroku Feed ID
#define UPDATE_INTERVAL 60000 // if the connection is good wait 60 seconds before updating again - should not be less than 5
#define RESET_INTERVAL 30000 // if connection fails/resets wait 30 seconds before trying again - should not be less than 5
#define heroku_API_KEY "F_oeCakGxHbk133xWCLNF6Z9sC01qCJ5cTfrOWl63oY" // fill in your API key 


int counterValue;

char *firsthalf;
char *secondhalf;

 
#define TankTempSensorPin 2
#define AmbientTempSenserPin 3
#define ledTestPin 13


#define ATO_High 8
 

#define mode99pb 50  // not used 
#define mode100pb 10// shelf light
#define mode101pb 12 // Feeding Mode
#define mode102pb 11 //WC Button  
#define mode103pb 50 //     
#define mode104pb 50  // not used
//47 feeding -  orange wire  103
///45 - ATO   100
// 44 - water change  101
// 43 reset 102

#define GCFI_Monitoring 9
/*
//Bottom
#define ATO_Valve 23 
#define Main_Pump 24
#define Heater 26
#define Reactor 27 
#define Chiller 50 //24
#define PowerHead 22
#define Skimmer 25

*/

 // bottom
 //1 = Skimmer
 //2 =  ATO Pump
 //3 =  Power head
 //4 =   Reactor
 //5 =  Main Pump
 //6 =  Heater
 //7 =  Grounding Plug
 //8 =  Spare Rec - used for Jebco powerhead


#define ATO_Valve 1
#define Main_Pump 4
#define Heater 5
#define Reactor 3
#define PowerHead 2
#define Skimmer 0
#define Grounding_plug 6
#define JeboPowerHead 7

#define RefugeLED 4 ///

#define relayPin3 34
#define relayPin4 37
#define relayPin1 55//35
#define relayPin2 36
#define Grounding_plug 50
#define Spare_Plug 50//26  // #6 plug ATS transformer

int relay_shelf_light = 3;   //30 working shelf light
//int relay_Refuge = 31;      //31  working refuge light

//1 = 31  - ATS pump  
//2 = 30 - Refuge Lights
//3 = 33 - Mainlights

 

// Menu and Keypad
byte menu = 1;
int keypadmode = 1;
int Main_Screen = 1;
int Temp_Screen = 2;
int Display_Lighting_Screen = 3;
int Pump_Control_Screen = 4;
int Refuge_System_Screen = 5;
int PH_Screen = 6;
int ATO_Screen = 7;
int Heater_Screen = 8;
int Chiller_Screen = 9;
int Feed_Mode_Screen = 10;
int System_Temp_Screen = 11;
int Omron_Relay_Screen = 12;
int Manual_Lighting_Control_Screen = 13;
int Set_Time_Date_Screen = 14;
int Temp_Trending = 15;
int LCD_Control_Screen = 16;
int heroku_Screen = 17;
int SetdatafromPOT1;
int SetdatafromPOT2;
int SetdatafromPOT3;
float SetdatafromPOTfloat1;
float SetdatafromPOTfloat2;
float SetdatafromPOTfloat3;

//Small //LCD
/*
int small_LCD_Screen = 1;
int S_L_Ambient_Screen = 1;
int S_L_PH_Screen = 9;
int S_L_heroku_Screen = 2; //was 3
int S_L_Last_Feeding_Screen = 3; //was 4
int S_L_Last_WaterChange_Screen = 10;//was 5
int S_L_ATO_Screen = 4; // was 6
int S_L_ATO_LAST_Screen = 5;
int return_to_first_screen = 6; // will put menu back to 1
boolean S_L_Screen_Updated; 
 */
// Heater
float Heater_on_temp = 78.50;  //Turn on the Heater at this temp         ex 78 degrees = 7800, 78.5 degrees = 7850
float Heater_off_temp = 79.00; //Turn off Heater at this temp
int Heater_on_Default_Address = 30; // Eeprom address Allow for 4 spots
int Heater_on_Default = 785; // Default Value  - Change "SetDefault" number if this value is changed
int Heater_off_temp_Default_Address = 35; // Eeprom address Allow for 4 spots
int Heater_off_temp_Default = 790;   // Default Value  - Change "SetDefault" number if this value is changed


int alarm_low_temp = 7600;  //alarm will begin if temp falls below this value & lights will turn on to raise the temperature
int alarm_high_temp = 8300;  //alarm will begin if temp is above this value
 
//ATO
int ato_time = 3; //Number of seconds for the ATO to run each time the switch is on.
int ATO_Hour;
int checklevel_ATOrunning = 0;
int checklevel_ATO = 0;
const float ATO_time = 9.00;
boolean ATOfaulted = LOW;
boolean ATOmoderun = LOW;
boolean ATO_Run_Next_Time = LOW;
int ATO_Start_Checking_time = 3;//Turn off power heads for this amount of time when feed mode button is pressed.
int ATO_off = -10; //placeholder  --don't change
int ATO_off_second, ATO_off_minute, ATO_on_minute, ATO_off_hour, ATO_on_second, ATO_on_hour, ATO_on;
 
float Started_ATO = 0.00;
float Fault_ATO_AT = 3.00;
boolean ATO_Got_Time = LOW;
boolean ATO_Got_Time_Pump = LOW;
boolean  sent_ato_fault_message_to_iphone = LOW;
 
int ATO_Fault_Count = 0;
float ATO_ran_last;
float ATO_delay_between_runs = 0.05;
float ATO_lenght_of_run = 0;
float ATO_delay_lenght_of_run = 0.05;
float Watchman_timer_ATO_AT = 0;
float Ato_okay_to_run_now = 0;
float Ato_Pump_last_ran = 0;
float Ato_okay_to_run_pump_now = 0;
float Run_Pump_for_only_timer = 0.03;
boolean start_delay_for_filled_timmer = false;
const float ATO_Master_On = 9; 
const float ATO_Master_Off = 21;

//Pump Controls
int feedmode = 0;
int feedmoderunning = 0;
boolean feedmoderun = LOW;
int feed_time = 15;  //Turn off power heads for this amount of time when feed mode button is pressed.
int pumps_off = -10; //placeholder  --don't change
int skimmer_off = -10;  //placeholder ---don't change
float skimmer_delay_start_time = 0;
float skimmer_delay_time = 0.05;  //5 minute start up delay
boolean skimmer_delay_bool = true;

float current_time = 0;

int pumps_off_second, pumps_off_minute, pumps_on_minute, pumps_off_hour, pumps_on_second, pumps_on_hour, pumps_on, skimmer_on_hour, skimmer_on_minute, skimmer_on_second;
int waterchangemoderunning = 0;
int waterchangemode = 0;
int WC_time = 35;  //Turn off power heads for this amount of time when feed mode button is pressed.
int WC_OFF = -10; //placeholder  --don't change
int WC_off_second, WC_off_minute, WC_on_minute, WC_off_hour, WC_on_second, WC_on_hour, WC_on;
 


//Mode Control
int mode = 100;
int mode100 = 0;
int mode101 = 0;
int mode102 = 0;
int mode103 = 0;
int mode104 = 0;
boolean lastButton99 = LOW;
boolean currentButton99 = LOW;
boolean lastButton100 = LOW;
boolean currentButton100 = LOW;
boolean lastButton101 = LOW;
boolean currentButton101 = LOW;
boolean lastButton102 = LOW;
boolean currentButton102 = LOW;
boolean lastButton103 = LOW;
boolean currentButton103 = LOW;
boolean lastButton104 = LOW;
boolean currentButton104 = LOW;

 
 

// Outputs
boolean GFCI_tripped = false;
boolean Found_Voltage_Problem = false;

boolean disableheater = false;
boolean disablemainpump = false;
boolean disablepowerhead = false;
boolean disablechiller = false; 
boolean disablerefugelight = false; 
boolean disableSkimmer = false; 

boolean set_Heater_output_to = false;
boolean set_chiller_output_to = false;
boolean set_mainpump_output_to = false;
boolean set_powerhead_output_to = false; 
boolean set_refugelight_output_to = false;
boolean set_Skimmer_output_to = false; 

boolean current_status_of_Main_Pump = false;
boolean current_status_of_PowerHead = false;
boolean current_status_of_Heater = false;
boolean current_status_of_Chiller = false;
boolean current_status_of_RefugeLED = false;
boolean current_status_of_ato_valve = false;
boolean current_status_of_water_level = false;
boolean current_status_of_Skimmer = false;

boolean pass_status_of_ato_valve = false;
boolean pass_status_of_Main_Pump = false;
boolean pass_status_of_PowerHead = false;
boolean pass_status_of_Heater = false;
boolean pass_status_of_Chiller = false;
boolean pass_status_of_RefugeLED = false;  
boolean pass_status_of_Skimmer = false; 

boolean  check_voltage_now = true;
boolean Voltage_detect = false;
boolean Found_Voltage_Problem_iphone_sent = false;
boolean GFCI_tripped_iphone_sent = false;
int Voltage_lastchecked;


float  Level_1_Overtemp = 82.50;
float  Level_2_Overtemp = 83.00;
float  Level_3_Overtemp = 84.00;
boolean  Over_temp_Level_1_message_sent = false;
boolean  Over_temp_Level_2_message_sent = false;
boolean  Over_temp_Level_3_message_sent = false;


// Refuge
const float FugeLightOn = 1; 
const float FugeLightOff = 9;
float FugeLightOFF12 = 0; 


//Light Shelf
 int light_shelf_off = -10;  //placeholder ---don't change
float light_shelf_delay_start_time = 0;
float light_shelf_delay_time = 0.02;  //5 minute start up delay
boolean light_shelf_delay_bool = true;
boolean light_shelf_is_on = false;
boolean turn_on_light_shelf = false;


// clock variables
uint16_t startAddr = 0x0000;            // Start address to store in the NV-RAM
uint16_t lastAddr;                      // new address for storing in NV-RAM
uint16_t TimeIsSet = 0xaa55;            // Helper that time must not set again

// global variables
byte curHour;
byte oldHour;

 
 

 

//// heroku 

//char heroku_data[128]; // this is the string to upload to heroku

float tempF_heroku;
float tempF2_heroku;
int Tanktemp_first_heroku;
int Tanktemp_second_heroku;

 
boolean temps_up = false;

float Ambient_tempF_heroku;
float Ambient_tempF2_heroku;
int Ambienttemp_first_heroku;
int Ambienttemp_second_heroku;
float AmbienttempC_Avg;

boolean Maintain_connection_sent = false;
char herokutext[20];
boolean last_connection_sent = false;

/// Main Tank Temp---------
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(TankTempSensorPin);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature TankSensor(&oneWire);
// arrays to hold device address
DeviceAddress TankThermometer;
float TanktempC;
float TanktempC_Avg;
float TanktempF;
float MTTEMPMAX = 90;
float MTTEMPMIN = 67;
/// Tank Temp Monitoring
int Tank_low_temp = 8900; // Send Message Tank at this temp
int Tank_high_temp = 84; // Send Message Tank at this temp
int Tank_TC; // Temp sensor mounted in the Tank
int Whole, Fract, High, Low; // Display High and Low
float  Main_Tank_High = 3;//history - 
float  Main_Tank_Low = 300;
boolean Main_Tank_Over_temp_message_sent = false;


/// Ambient Temp---------
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire_Ambient(AmbientTempSenserPin);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature AmbientSensor(&oneWire_Ambient);
// arrays to hold device address
DeviceAddress AmbientThermometer;
float AmbienttempC;
float AmbienttempF;
float AmbientTEMPMAX = 90;
float AmbientTEMPMIN = 67;
/// Tank Temp Monitoring
int Ambient_low_temp = 8900; // Send Message Tank at this temp
int Ambient_high_temp = 8900; // Send Message Tank at this temp
int Ambient_TC; // Temp sensor mounted in the Tank
int AmbientWhole, AmbientFract, AmbientHigh, AmbientLow; // Display High and Low
float  Ambient_High = 3;//history - 
float  Ambient_Low = 300;
float Ambient_tempF_heroku_2;
float Tank_tempF_heroku_2;


  
  

// Ambient Temp Averaging
const int Ambient_Temp_Avg_numReadings = 15;
int Ambient_Temp_Avg_readings[Ambient_Temp_Avg_numReadings];      // the readings from the analog input
int Ambient_Temp_Avg_index = 0;                  // the index of the current reading
int  Ambient_Temp_Avg_total = 0;                  // the running total
float  Ambient_Temp_Avg_average = 0;   
int Ambient_Temp_Avg_index_2 = 0; // the average 

// Tank Temp Averaging 
const int Tank_Temp_Avg_numReadings = 2;
int Tank_Temp_Avg_readings[Tank_Temp_Avg_numReadings];      // the readings from the analog input
int Tank_Temp_Avg_index = 0;                  // the index of the current reading
int Tank_Temp_Avg_total = 0;                  // the running total
float Tank_Temp_Avg_average = 0;                // the average
int Tank_Temp_Avg_index_2 = 0; 

 



 



///// --------------------------VOID SETUP ------------------------------------------------------------------------------------------

void setup() {
  Wire.begin();

   Serial.begin(57600);
  // give the ethernet module time to boot up:

Serial.print("starting up");
  // ATO
  pinMode(ATO_High, INPUT);
  
  //
    pinMode(relay_shelf_light, OUTPUT);
//  pinMode(relay_Refuge, OUTPUT); 
 
  // Push Buttons
  pinMode(mode99pb, INPUT);
  pinMode(mode100pb, INPUT);
  pinMode(mode101pb, INPUT);
  pinMode(mode102pb, INPUT);
  pinMode(mode103pb, INPUT);
  pinMode(mode104pb, INPUT);
  pinMode(GCFI_Monitoring, INPUT);
  //LED on Arduino Board
  pinMode(ledTestPin, OUTPUT);  //we'll use the debug LED to output a heartbeat

  //Buzzer
 // pinMode(buzzerPin, OUTPUT);

bottom_relays.digitalWrite(0, LOW); // Turn off led 2

  // Relays
  
  /*
  pinMode(ATO_Valve, OUTPUT);
  
  pinMode(Main_Pump, OUTPUT);
  pinMode(Heater, OUTPUT);
  pinMode(Chiller, OUTPUT);
  pinMode(PowerHead, OUTPUT);
  pinMode(RefugeLED, OUTPUT);
  pinMode(Spare_Plug, OUTPUT);
  pinMode(Reactor, OUTPUT);
  pinMode(Skimmer, OUTPUT);
  pinMode(Grounding_plug, OUTPUT);
  digitalWrite(Grounding_plug, HIGH);//was low 
 */
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
 
 Serial.print("1");
   /* Start I2C bus and PCF8574 instance */
  //top_relays.begin(0x21);
   Serial.print("red");
  top_relays.begin(redchip);
   Serial.print("green");
  bottom_relays.begin(greenchip);
 // buttons.begin(greenchip);

  Serial.print("1a");
  
  /* Setup some PCF8575 pins for demo */
  top_relays.pinMode(0, OUTPUT);
  top_relays.pinMode(1, OUTPUT);
  top_relays.pinMode(2, OUTPUT);
  top_relays.pinMode(3, OUTPUT);
  top_relays.pinMode(4, OUTPUT);
  top_relays.pinMode(5, OUTPUT);
  top_relays.pinMode(6, OUTPUT);
  top_relays.pinMode(7, OUTPUT);
  
    /* Setup some PCF8575 pins for demo */
  bottom_relays.pinMode(0, OUTPUT);
  bottom_relays.pinMode(1, OUTPUT);
  bottom_relays.pinMode(2, OUTPUT);
  bottom_relays.pinMode(3, OUTPUT);
  bottom_relays.pinMode(4, OUTPUT);
  bottom_relays.pinMode(5, OUTPUT);
  bottom_relays.pinMode(6, OUTPUT);
  bottom_relays.pinMode(7, OUTPUT);
  
    /* Setup some PCF8575 pins for demo 
  buttons.pinMode(0, INPUT_PULLUP);
  buttons.pinMode(1, INPUT_PULLUP);
  buttons.pinMode(2, INPUT_PULLUP);
  buttons.pinMode(3, INPUT_PULLUP);
  buttons.pinMode(4, INPUT_PULLUP);
  buttons.pinMode(5, INPUT_PULLUP);
  buttons.pinMode(6, INPUT_PULLUP);
  buttons.pinMode(7, INPUT_PULLUP);
  */
  
  
  top_relays.digitalWrite(0, HIGH); 
  top_relays.digitalWrite(1, HIGH); 
  top_relays.digitalWrite(2, HIGH); 
  top_relays.digitalWrite(3, HIGH); 
  top_relays.digitalWrite(4, HIGH); 
  top_relays.digitalWrite(5, HIGH); 
  top_relays.digitalWrite(6, HIGH); 
  top_relays.digitalWrite(7, HIGH); 
  
  bottom_relays.digitalWrite(0, HIGH); 
  bottom_relays.digitalWrite(1, HIGH); 
  bottom_relays.digitalWrite(2, HIGH); 
  bottom_relays.digitalWrite(3, HIGH); 
  bottom_relays.digitalWrite(4, HIGH); 
  bottom_relays.digitalWrite(5, HIGH); 
  bottom_relays.digitalWrite(6, HIGH);
  bottom_relays.digitalWrite(7, HIGH);  
 
 

 //  digitalWrite(relay_Refuge, LOW); // Refuge light
  top_relays.digitalWrite(relay_shelf_light, HIGH); // Shelf  light
  top_relays.digitalWrite(RefugeLED, HIGH);
  
 // bottom
 //1 = Skimmer
 //2 =  ATO Pump
 //3 =  Power head
 //4 =   Reactor
 //5 =  Main Pump
 //6 =  Heater
 //7 =  Grounding Plug
 //8 =  Spare Rec - used for Jebco powerhead

  // relay default value
  bottom_relays.digitalWrite(Skimmer, HIGH);
  bottom_relays.digitalWrite(ATO_Valve, HIGH);
  bottom_relays.digitalWrite(PowerHead, LOW);
  bottom_relays.digitalWrite(JeboPowerHead, LOW);
   
  bottom_relays.digitalWrite(Reactor, LOW);
 
  bottom_relays.digitalWrite(Main_Pump, LOW);
  bottom_relays.digitalWrite(Heater, LOW);
  
  
  
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
  digitalWrite(relayPin4, HIGH);
  
 
  Serial.print("2");
  
  // start clock
  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));


   if (TimeIsSet != 0xaa58)
  {
    Serial.println("INFO:Time is not defined. Set time now.");
    RTC.stopClock();
    RTC.fillByYMD(2014, 04, 26);
    RTC.fillByHMS(19, 47, 00);
    RTC.setTime();
    RTC.startClock();
    TimeIsSet = 0xaa58;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  }


  // Control Register for SQW pin which can be used as an interrupt.

  RTC.ctrl = 0x00; // 0x00=disable SQW pin, 0x10=1Hz, 0x11=4096Hz, 0x12=8192Hz, 0x13=32768Hz
  RTC.setCTRL();
 

   RTC.getTime();
 
  skimmer_delay_start_time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600); 
  skimmer_delay_bool = true;
  //LCD.Clear();
 
  current_time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);


 

  // Start up the library for Tank Sensor
  TankSensor.begin();
  if (!TankSensor.getAddress(TankThermometer, 0)) Serial.println("Unable to connect with Tank Temp Sensor");
  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  TankSensor.setResolution(TankThermometer, 9);

  // Start up the library for Tank Sensor
  AmbientSensor.begin();
  if (!AmbientSensor.getAddress(AmbientThermometer, 0)) Serial.println("Unable to connect with Ambient Temp Sensor");
  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  AmbientSensor.setResolution(AmbientThermometer, 9);
 
 

 

  //LCDsmall.clear();

  Serial.print("running tank temp_______________");
  TankSensor.requestTemperatures(); // Send the command to get temperatures
  TanktempC = TankSensor.getTempC(TankThermometer);
  Serial.print("Tank temp is:");
  Serial.println(DallasTemperature::toFahrenheit(TanktempC)); // Converts TanktempC to Fahrenheit
  int tempforcheck = TanktempC;
  if(tempforcheck <= 3 || tempforcheck >= 70)
  {

    // reset temp.sensor
    // Start up the library
    TankSensor.begin();
    if (!TankSensor.getAddress(TankThermometer, 0)) Serial.println("Unable to connect with Tank Temp Sensor"); 
    // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
    TankSensor.setResolution(TankThermometer, 9);
    TankSensor.requestTemperatures(); // Send the command to get temperatures
    TanktempC = TankSensor.getTempC(TankThermometer);
    Serial.print("Tank temp is");
    Serial.println(DallasTemperature::toFahrenheit(TanktempC)); 
  }


Serial.print("Tank temp is");

Serial.println(TanktempC);
  Serial.print("running Ambient temp_______________");
  AmbientSensor.requestTemperatures(); // Send the command to get temperatures
  AmbienttempC = AmbientSensor.getTempC(AmbientThermometer);
  Serial.print("Ambient temp is:");
  Serial.println(DallasTemperature::toFahrenheit(AmbienttempC)); // Converts AmbienttempC to Fahrenheit
  int Ambient_tempforcheck = AmbienttempC;
  if(Ambient_tempforcheck <= 3 || Ambient_tempforcheck >= 70)
  {

    // reset temp.sensor
    // Start up the library
    AmbientSensor.begin();
    if (!AmbientSensor.getAddress(AmbientThermometer, 0)) Serial.println("Unable to connect with Ambient Temp Sensor"); 
    // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
    AmbientSensor.setResolution(AmbientThermometer, 9);
    AmbientSensor.requestTemperatures(); // Send the command to get temperatures
    AmbienttempC = AmbientSensor.getTempC(AmbientThermometer);
    Serial.print("Ambient temp is");
    Serial.println(DallasTemperature::toFahrenheit(AmbienttempC)); 
  }


  // initialize all the readings to 0:  
  for (int Ambient_Temp_Avg_thisReading = 0; Ambient_Temp_Avg_thisReading < Ambient_Temp_Avg_numReadings; Ambient_Temp_Avg_thisReading++)
    Ambient_Temp_Avg_readings[Ambient_Temp_Avg_thisReading] = 0;            
  for (int Tank_Temp_Avg_thisReading = 0; Tank_Temp_Avg_thisReading < Tank_Temp_Avg_numReadings; Tank_Temp_Avg_thisReading++)
    Tank_Temp_Avg_readings[Tank_Temp_Avg_thisReading] = 0;            
 

  counterValue = 10;
 
 turn_on_shelf_light();

 Serial.print("started up");
}



///// --------------------------VOID LOOP -------------------------------------------------------------------------------------------
void loop() {
  
 RTC.getTime();

current_time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600);
 // Serial.println("Blink Test Led");
  blinkTestLed();
 
 //  Serial.println("Check GFCI");
  
 // checkGFCI();
 
 
 
 
 // Serial.println("get Temps");
  GetTemps();
 // Serial.println("overtemp Protection");
  overtemp_protection();
 // Serial.println("Check Mode");
  checkmode();
 // Serial.println("print Date");
  printDate();
  // printPH();
 
//  Serial.println("print temp");
 
 // Serial.println("Run Fuge Light");
  RunFugelight();
//  Serial.println("Print Heater");
   printHeater();
//  Serial.println("Print Chiller");
 
 
 
//  Serial.println("Feeding Mode");
  FeedingMode();
//  Serial.println("Water Change Mode");
  WaterChangeMode();
 
 
 
  
 // Serial.println("outputs");
  outputs();
  // Voltage_Detected_Where();  use when voltage sensor is attached
  //Reset_Voltage_Fault();  // will cause a continully reset
  
  //Serial.println("SChekc for Voltage");
 
    
//Serial.println("Status of heroku info");
//  status_of_heroku_info();
 // Serial.println("Print Ambient Temp");
 
 // Serial.println("heroku Screen Controls");
 // heroku_Screen_controls();
 // Serial.println("Small //LCD Controller");
 
 // Serial.println("Maintain heroku Connection");
 
//  Maintain_heroku_connection();

  /// Test_ATO();  // Used to test inputs and outputs only
 
//Serial.println("ATO");
 ATO();
 // Serial.println("Screen ATO");
  Screen_ATO();
 Skimmer_Controller();
 
 
 Light_shelf_Controller();

}


 


void Skimmer_Controller(){
  
 float current_time  = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600); 
 float turn_on_skimmer_when;
 
   if (skimmer_delay_bool == true ){
turn_on_skimmer_when = skimmer_delay_start_time + skimmer_delay_time;
   }
 
  if(waterchangemode == 1 || waterchangemoderunning == 1 || feedmoderunning == 1){
       skimmer_delay_bool = true;
       
       } 
 
 if (current_time  >= turn_on_skimmer_when){
   if (skimmer_delay_bool == true ){
   
   
     
       if(waterchangemode == 1 || waterchangemoderunning == 1 || feedmoderunning == 1){
       
       
       }else{
         set_Skimmer_output_to = true; 
         skimmer_delay_bool = false; 
       }
   
   
 
 
   }
 
 }
 
  
}

 

 
void blinkTestLed()
{
  if(digitalRead(ledTestPin))
    digitalWrite(ledTestPin, LOW); 
  else
    digitalWrite(ledTestPin, HIGH); 
}


//_______________________DATE ____________________________________________________
void printDate()
{
  uint8_t  hour12;
  RTC.getTime();
  char text[24];

  if (RTC.hour >= 13){
    hour12 = RTC.hour;
    hour12 = hour12 - 12;
    sprintf(text, "  %02d:%02d:%02d:PM", hour12, RTC.minute, RTC.second);
  }
  else{
    hour12 = RTC.hour;
    sprintf(text, "  %02d:%02d:%02d:AM", hour12, RTC.minute, RTC.second);
  }
  ////LCDsmall.setCursor(0, 1);
  ////LCDsmall.print(text); 

  //sprintf(text, "Time: %02d:%02d:%02d :AM", hour12, RTC.minute, RTC.second);
  if(keypadmode == 1 || keypadmode == 3){
    //LCD.setCursor(0, 7);
    //LCD.print(text);
  }

  if(keypadmode == Refuge_System_Screen){
    //LCD.setCursor(0, 2);
    //LCD.print(text);
  }
  // Serial.println(text);
}



///-------------------Heater control--------------------------------------
void printHeater()
{
  float Tank_tempF =(DallasTemperature::toFahrenheit(TanktempC)); // Converts TanktempC to Fahrenheit

  ///  put heater cut off here
  //Serial.println(Tank_tempF);
  //Serial.println(Heater_on_temp);
  if(Tank_tempF < Heater_on_temp){     // turn Heater on if temp is below Heater_on_temp
    // Turn Heater On     
    set_Heater_output_to = true;    
  
    // Serial.println("*****  Heater ON *****");
  }  
  int tank_tempf =  Tank_tempF;
  if(tank_tempf > 100){     // turn Heater on if temp is below Heater_on_temp
    // Turn Heater On      
    set_Heater_output_to = true;  
     
    //  Serial.println("*****  Heater ON *****");
  }  
  else {
    if(Tank_tempF > Heater_off_temp){    //turn Heater off if temp is above Heater_off_temp
      // Turn Heater Off     
      set_Heater_output_to = false;     
    
      //   Serial.println("*****  Heater OFF *****");
    }
  }
  if(keypadmode == Temp_Screen){
    //LCD.GotoXY(0,6);           
    if(digitalRead(Heater) == LOW){
      //LCD.print("Heater  :  ON ");
    }
    else{
      //LCD.print("Heater  : Off");
    }
  }

  if(keypadmode == Heater_Screen){

    //LCD.setCursor(0, 2);
    //LCD.print("Tank: "); 
    float tempF =(DallasTemperature::toFahrenheit(TanktempC)); // Converts TanktempC to Fahrenheit
    //LCD.print(tempF); 
    //LCD.print(" F"); 

    //LCD.GotoXY(0,4);
    //LCD.print("Turn  ON: ");  

    //LCD.print(Heater_on_temp);
    //LCD.GotoXY(0,5);
    //LCD.print("Turn OFF: ");  

    //LCD.print(Heater_off_temp);
    //LCD.GotoXY(0,7); 

    if(digitalRead(Heater) == LOW){
      //LCD.print("Heater:  ON ");
    }
    else{
      //LCD.print("Heater: Off");
    }
  }
  
  
}


 
 
 

void WaterChangeMode(){

  





  if(waterchangemode == 1 || waterchangemoderunning == 1 ){
    /// WaterChange mode running
    //  Serial.print("WaterChange mode active");
 

    // Turn mainpump Off      
    set_mainpump_output_to = false;  
   // Turn Skimmer Off 
   set_Skimmer_output_to = false; 
    // Turn powerhead Off       
    set_powerhead_output_to = false;    

    

    waterchangemoderunning = 1;
    feedmode = 3;

  }
  else{
    // Run Pumps
    if(feedmode == 3 || feedmoderunning == 1 || checklevel_ATOrunning == 1 || checklevel_ATO == 1){

    }
    else{
      // Turn mainpump On      
      set_mainpump_output_to = true;  
      //Turn Skimmer On
      set_Skimmer_output_to = true; 
 
      
    }

    // Turn powerhead On       
    set_powerhead_output_to = true;       
    
  }
  waterchangemode = 0;   



  if(waterchangemoderunning == 1 ){

    if(keypadmode == Main_Screen){ 
      //LCD.GotoXY(0,6);
      //LCD.print("W/C Mode Active");
    } 
    if(keypadmode == Pump_Control_Screen){ 
      //LCD.GotoXY(0,6);
      //LCD.print("W/C Mode Active");
    } 
  }

 
}

void FeedingMode(){

  //Pump mode 4 
  //Feed Mode Settings mode 10
  if(keypadmode == Pump_Control_Screen){ 
    //LCD.GotoXY(0,6);
    //LCD.print("Feeding Mode:");
  }


  if(keypadmode == Feed_Mode_Screen){ 
    //LCD.GotoXY(0,6);
    //LCD.print("Feeding Mode:");
  }


 


  if(feedmode == 1){ 
    Serial.print("feeding mode active");


 

    if(keypadmode == Main_Screen){ 
      //LCD.GotoXY(0,6);
      //LCD.print("FeedMode:Active");
    }


    // if(feedmode == 1 && digitalRead(Main_Pump) == HIGH){
    pumps_off = 10;

    pumps_on_second = RTC.second;
    if(RTC.minute + feed_time > 59){
      pumps_on_minute = (RTC.minute + feed_time) % 60;
      pumps_on_hour = RTC.hour + 1;
    }
    else{
      pumps_on_minute = RTC.minute + feed_time;
      pumps_on_hour = RTC.hour;
    }

    if(pumps_on_hour > 23){
      pumps_on_hour = pumps_on_hour - 24;
    }

  }

  if(feedmode == 3 && feedmoderunning == 1){
    pumps_off = -10; // turns off feeding mode

    if(keypadmode == Feed_Mode_Screen || keypadmode == Pump_Control_Screen){ 
      //LCD.GotoXY(0,6);
      //LCD.print("             ");
    }



    if(keypadmode == Main_Screen){ 
      //LCD.GotoXY(0,6);
      //LCD.print("               ");
    }
  }

  if((pumps_on_hour == RTC.hour  && pumps_on_minute == RTC.minute  && pumps_on_second <= RTC.second) || pumps_off == -10){

    if(waterchangemode == 1 || waterchangemoderunning == 1 ){
    }
    else{
      // Turn mainpump On     
      set_mainpump_output_to = true;  
      set_Skimmer_output_to = true; 
  
  if (skimmer_delay_bool == false && set_Skimmer_output_to == false){
   skimmer_delay_start_time = RTC.hour + ((float)RTC.minute / (float)60) + ((float)RTC.second / (float)3600); 
  skimmer_delay_bool = true;
  skimmer_delay_time = 0.45;
    Serial.println("setting time in Feeding Mode");
  
    }
      
    }
    feedmoderunning = 0;
    pumps_off = -10;

  }
  else{ 


    if(waterchangemode == 1 || waterchangemoderunning == 1 || ATOmoderun == HIGH){




    }
    else{
      // Turn mainpump Off    
      set_mainpump_output_to = false;
       set_Skimmer_output_to = false;  
      

    }
    feedmoderun = HIGH;
    feedmoderunning = 1;

  }

  //Display when normal operation will resume*******************
  if(pumps_off != -10){
    if(keypadmode == Pump_Control_Screen){ 
      //LCD.setCursor(3,7); 
    }
    if(keypadmode == Feed_Mode_Screen){ 
      //LCD.setCursor(3,7); 
    }
    if(pumps_on_minute >= RTC.minute){
      pumps_off_second = pumps_on_second - RTC.second + feed_time * 60 + pumps_on_minute * 60 - RTC.minute * 60 - feed_time * 60;
    }
    else{
      pumps_on = RTC.minute - 60;
      pumps_off_second = pumps_on_second - RTC.second + feed_time * 60 + pumps_on_minute * 60 - pumps_on * 60 - feed_time * 60;
    }

    pumps_off_minute = pumps_off_second / 60;

    if(pumps_off_minute < 10){
      if(keypadmode == Pump_Control_Screen || keypadmode == Feed_Mode_Screen){ 
        //LCD.print(" ");
      }
    }
    if(keypadmode == Pump_Control_Screen || keypadmode == Feed_Mode_Screen){ 
      //LCD.print(pumps_off_minute);  //minutes until pumps turn on 
      //LCD.print(":"); 
    }
    if(pumps_off_second % 60 < 10){
      if(keypadmode == Pump_Control_Screen || keypadmode == Feed_Mode_Screen){ 
        //LCD.print("0");
      } 
    }
    if(keypadmode == Pump_Control_Screen || keypadmode == Feed_Mode_Screen){ 
      //LCD.print(pumps_off_second % 60);  //seconds until pumps turn on 
    }

  }
  else{

    if(feedmoderun == HIGH){
      //LCD.Clear();
      feedmoderun = LOW;
    }

    if(keypadmode == Pump_Control_Screen || keypadmode == Feed_Mode_Screen){ 
      //LCD.setCursor(3,7);
      //LCD.print(" Not Active");
    }

  }

  feedmode = 0;
  
}

 



  
void outputs(){
  // should be the only place the “digitalwrite” for a output is used
  // Heater Control
  if (set_Heater_output_to == true && disableheater == false ){

    bottom_relays.digitalWrite(Heater, LOW);
  }
  else{
    bottom_relays.digitalWrite(Heater, HIGH);
  }
  // Main Pump Control

  if (set_mainpump_output_to == true && disablemainpump == false){

   bottom_relays.digitalWrite(Main_Pump, LOW);
  }
  else{
   bottom_relays.digitalWrite(Main_Pump, HIGH);
  }
  // PowerHead Control
  if (set_powerhead_output_to == true && disablepowerhead == false){

    bottom_relays.digitalWrite(PowerHead, LOW);
    bottom_relays.digitalWrite(JeboPowerHead, LOW);
  }
  else{
    bottom_relays.digitalWrite(PowerHead, HIGH);
    bottom_relays.digitalWrite(JeboPowerHead, LOW);
  }
  // Chiller Control
  if (set_chiller_output_to == true && disablechiller == false){

  //  digitalWrite(Chiller, LOW);
  }
  else{
  //  digitalWrite(Chiller, HIGH);
  }
  
  // Refuge light Control
  if (set_refugelight_output_to == true && disablerefugelight == false){

   top_relays.digitalWrite(RefugeLED, LOW);
  }
  else{
    top_relays.digitalWrite(RefugeLED, HIGH);
  }



  // Skimmer Control
  if (set_Skimmer_output_to == true && disableSkimmer == false ){

    bottom_relays.digitalWrite(Skimmer, LOW);
  }
  else{
    bottom_relays.digitalWrite(Skimmer, HIGH);
  }


  

}


 

const char* ip_to_str(const uint8_t* ipAddr)
{
  static char buf[16];
  sprintf(buf, "%d.%d.%d.%d\0", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
  return buf;
}

// Shelf Light 
int shelf_lights = 0;
int shelf_lightsrunning = 0;
boolean shelf_lightsrun = LOW;
int shelf_light_time = 1;  //Turn off power heads for this amount of time when feed mode button is pressed.
int shelf_lights_off, shelf_lights_off_second, shelf_lights_off_minute, shelf_lights_on_minute, shelf_lights_off_hour, shelf_lights_on_second, shelf_lights_on_hour, shelf_lights_on;




