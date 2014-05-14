

///-------------------TEMP--------------------------------------
void printTemp()
{

  float tempF;
  int tempforcheck;

  if(RTC.second == 30){ 

    tempF =(DallasTemperature::toFahrenheit(TanktempC)); // Converts TanktempC to Fahrenheit
    tempforcheck = TanktempC;



  }

  if( keypadmode == 1 || keypadmode == Temp_Screen){

    if( keypadmode == Temp_Screen){  
      //LCD.setCursor(0, 2);
    }
    if( keypadmode == 1){  
      //LCD.setCursor(0, 3);
    }
    //LCD.print("Tank:"); 
    // correct this code to use tanktempf float

      if( keypadmode == Temp_Screen){
      //LCD.setCursor(6, 2);
    } 
    if( keypadmode == 1){
      //LCD.setCursor(6, 3);
    }
    tempF =(DallasTemperature::toFahrenheit(TanktempC)); // Converts TanktempC to Fahrenheit

    tempforcheck = TanktempC;
    if(tempforcheck <= 3 || tempforcheck >= 70)
    { 
      //LCD.print("T:Error"); 
    } 
    else{
      //LCD << _FLOAT(tempF, 1) << _BYTE(223) << " F ";
#ifdef DEBUG
      // Serial << "Temp = " << _FLOAT(TanktempC, 1) << "C" << endl;
#endif  


      //Display High Temp***************************************************************************************

      if(RTC.second == 30){  //used so if bad data is sent for the first reading, it is not saved

        if(tempF > Main_Tank_High){
          Main_Tank_High = tempF;
        }
      }
      if( keypadmode == Temp_Screen){ 
        //LCD.setCursor(0, 4);
        //LCD.print("Max Temp: "); 
        //LCD.print(Main_Tank_High);  
      }

      //Display Low Temp***************************************************************************************
      if(RTC.second == 30){  //used so if bad data is sent for the first reading, it is not saved
        if(tempF < Main_Tank_Low){
          Main_Tank_Low = tempF;
        }
      }

      if( keypadmode == Temp_Screen){ 
        //LCD.setCursor(0, 5);
        //LCD.print("Min Temp: "); 
        //LCD.print(Main_Tank_Low);
      } 
    }
  }
//    Serial.println(tempF);
//   Serial.println(Tank_high_temp);
  if(Tank_Temp_Avg_average >= Tank_high_temp){

    /*
    if(Main_Tank_Over_temp_message_sent == false){
     Serial.println("tank is over tmep send iphone message *******************************************");
     
     int Tanktemp_first = tempF; ////  makes 26.7 into 26
     int TempF2 = tempF * 100;////  makes 26.7 into 2670
     int TempF3 = Tanktemp_first * 100; /// makes 26 into 2600
     int Tanktemp_second = TempF2 - TempF3;
     // heroku_in_out();
     ////Send_message_to_iphone("Tank Temp over 80F", "start to panic");
     char tempdata[20];
     sprintf (tempdata, "The Tank temp is: %d.%d", Tanktemp_first, Tanktemp_second); 
     Serial.println(tempdata);
     
     //Send_message_to_iphone(tempdata, "start to panic");
     Main_Tank_Over_temp_message_sent = true;
     heroku_in_out();
     }
     */
  }
  else{
    Main_Tank_Over_temp_message_sent = false; 
  }


} 


void printAmbientTemp()
{

  float Ambient_tempF;
  int Ambient_tempforcheck;

  if(RTC.second == 30){ 

    Ambient_tempF =(DallasTemperature::toFahrenheit(AmbienttempC)); // Converts AmbienttempC to Fahrenheit
    Ambient_tempforcheck = AmbienttempC;




  }


  if( keypadmode == 1){  
    //LCD.setCursor(0, 4);

    //LCD.print("Ambient:"); 



    //LCD.setCursor(9, 4);

    Ambient_tempF =(DallasTemperature::toFahrenheit(AmbienttempC)); // Converts AmbienttempC to Fahrenheit

    Ambient_tempforcheck = AmbienttempC;
    if(Ambient_tempforcheck <= 3 || Ambient_tempforcheck >= 70)
    { 
      //LCD.print("T:Error"); 
    } 
    else{
      //LCD << _FLOAT(Ambient_tempF, 1) << _BYTE(223) << " F";
#ifdef DEBUG
      // Serial << "Temp = " << _FLOAT(AmbienttempC, 1) << "C" << endl;
#endif  

    }
    //Display High Temp***************************************************************************************

    if(RTC.second == 30){  //used so if bad data is sent for the first reading, it is not saved

      if(Ambient_tempF > Ambient_High){
        Ambient_High = Ambient_tempF;
      }
    }
    if( keypadmode == Temp_Screen){ 
      //LCD.setCursor(0, 6);
      //   //LCD.print("Max Temp: "); 
      //   //LCD.print(Ambient_High);  
    }

    //Display Low Temp***************************************************************************************
    if(RTC.second == 30){  //used so if bad data is sent for the first reading, it is not saved
      if(Ambient_tempF < Ambient_Low){
        Ambient_Low = Ambient_tempF;
      }
    }

    if( keypadmode == Temp_Screen){ 
      //LCD.setCursor(0, 7);
      //   //LCD.print("Min Temp: "); 
      //    //LCD.print(Ambient_Low);
    } 

  }




} 


void printTemp_on_smallLCD()
{
  float tempF;
  int tempforcheck;
  float Ambient_tempF;
  int Ambient_tempforcheck;


  tempforcheck = TanktempC;

  tempF =(DallasTemperature::toFahrenheit(TanktempC));
  //LCDsmall.setCursor(0, 0);
  if(tempforcheck <= 3 || tempforcheck >= 70)
  { 
    //LCDsmall.print("Tank =  T:Error");  ////LCDsmall.setCursor(0, 1);
  } 
  else{
    //LCDsmall << "Tank = "  << _FLOAT(tempF, 1) << _BYTE(223) << "F   ";
  }


  Ambient_tempforcheck = AmbienttempC;

  Ambient_tempF =(DallasTemperature::toFahrenheit(AmbienttempC));
  //LCDsmall.setCursor(0, 1);


  if(small_LCD_Screen == S_L_Ambient_Screen){

    if(Ambient_tempforcheck <= 3 || Ambient_tempforcheck >= 70)
    { 
      //LCDsmall.print("Ambient = T:Error"); 
    } 
    else{
      //LCDsmall << "Ambient = "  << _FLOAT(Ambient_tempF, 1) << _BYTE(223) << "F   ";
    }
  }



}

 
 


void GetTemps(){


  if (RTC.second == 23)
  { 
    //Serial.print("running Ambient temp_______________");
    AmbientSensor.requestTemperatures(); // Send the command to get temperatures
    AmbienttempC = AmbientSensor.getTempC(AmbientThermometer);
    //Serial.print("Ambient temp is:");
    //Serial.println(DallasTemperature::toFahrenheit(AmbienttempC)); // Converts AmbienttempC to Fahrenheit
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
      Serial.println(DallasTemperature::toFahrenheit(AmbienttempC)); // Converts AmbienttempC to Fahrenheit
    }


  }

  if(AmbienttempC_Avg != AmbienttempC){

    int ambeint_transfer = AmbienttempC * 10;

    // Ambient Temp Average ******   // subtract the last reading:
    Ambient_Temp_Avg_total = Ambient_Temp_Avg_total - Ambient_Temp_Avg_readings[Ambient_Temp_Avg_index];  
    //Serial.println(Ambient_Temp_Avg_total);
    // read from the sensor:  
    Ambient_Temp_Avg_readings[Ambient_Temp_Avg_index] = ambeint_transfer; // add the reading to the total:
    //Serial.println(Ambient_Temp_Avg_readings);
    Ambient_Temp_Avg_total= Ambient_Temp_Avg_total + Ambient_Temp_Avg_readings[Ambient_Temp_Avg_index];   // advance to the next position in the array: 
    //Serial.println(Ambient_Temp_Avg_total);

    Ambient_Temp_Avg_index = Ambient_Temp_Avg_index + 1;  
    // Serial.println(Ambient_Temp_Avg_index);
    // if we're at the end of the array...
    if (Ambient_Temp_Avg_index_2 < Ambient_Temp_Avg_numReadings)  {             
      Ambient_Temp_Avg_index_2 = Ambient_Temp_Avg_index_2 + 1;         
    }    
    else{
    }            

    if (Ambient_Temp_Avg_index >= Ambient_Temp_Avg_numReadings)  {             
      Ambient_Temp_Avg_index = 1;          
    }    
    else{
    }               // calculate the average:
    float Ambient_Temp_Avg_average_0 = Ambient_Temp_Avg_total / Ambient_Temp_Avg_index_2;  // send it to the computer as ASCII digits

    Ambient_Temp_Avg_average = Ambient_Temp_Avg_average_0 / 10;

    AmbienttempC_Avg = AmbienttempC;

  }



  // Tank Sensor

  if (RTC.second == 24)
  { 
    //Serial.print("running tank temp_______________");
    TankSensor.requestTemperatures(); // Send the command to get temperatures
    TanktempC = TankSensor.getTempC(TankThermometer);
   // Serial.print("Tank temp is:");
   // Serial.println(DallasTemperature::toFahrenheit(TanktempC)); // Converts TanktempC to Fahrenheit
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
      Serial.println(DallasTemperature::toFahrenheit(TanktempC)); // Converts TanktempC to Fahrenheit
    }
  }
  if(TanktempC_Avg != TanktempC){

    int tank_transfer = TanktempC * 10;
    // TankTemp Average ******  

    // subtract the last reading:

    Tank_Temp_Avg_total = Tank_Temp_Avg_total - Tank_Temp_Avg_readings[Tank_Temp_Avg_index];          // read from the sensor:  

    Tank_Temp_Avg_readings[Tank_Temp_Avg_index] = tank_transfer;  // add the reading to the total:

    Tank_Temp_Avg_total = Tank_Temp_Avg_total + Tank_Temp_Avg_readings[Tank_Temp_Avg_index];        // advance to the next position in the array:  

    Tank_Temp_Avg_index = Tank_Temp_Avg_index + 1;                    
    // if we're at the end of the array...
    if (Tank_Temp_Avg_index_2 < Tank_Temp_Avg_numReadings)  {             
      Tank_Temp_Avg_index_2 = Tank_Temp_Avg_index_2 + 1;         
    }    
    else{
    }            

    if (Tank_Temp_Avg_index >= Tank_Temp_Avg_numReadings) {             
      // ...wrap around to the beginning:   
      Tank_Temp_Avg_index = 0;     
    }
    else{
    }                       // calculate the average:
    float Tank_Temp_Avg_average_0 = Tank_Temp_Avg_total / Tank_Temp_Avg_index_2;          // send it to the computer as ASCII digits
    // Serial.print("Tank_Temp_Avg_average");  
    //Serial.println(Tank_Temp_Avg_average);  

    Tank_Temp_Avg_average = Tank_Temp_Avg_average_0 / 10;

    TanktempC_Avg = TanktempC;

  }


   
   

   

}

void overtemp_protection(){

  float tempF_Overtime = 0;


  tempF_Overtime =(DallasTemperature::toFahrenheit(Tank_Temp_Avg_average)); // Converts Tank_Temp_Avg_average to Fahrenheit
/*
  Serial.print("tempF-Overtime:");
  Serial.println(tempF_Overtime);
  Serial.print("Tank_Temp_Avg_average:");
  Serial.println(Tank_Temp_Avg_average);
*/

  if(tempF_Overtime > Level_1_Overtemp){

    // Level 1 of the Overtemp Correct Plan in use
    if(Over_temp_Level_1_message_sent == false){

      int Tanktemp_first = tempF_Overtime; ////  makes 26.7 into 26
      int TempF2 = tempF_Overtime * 100;////  makes 26.7 into 2670
      int TempF3 = Tanktemp_first * 100; /// makes 26 into 2600
      int Tanktemp_second = TempF2 - TempF3;
       
      ////Send_message_to_iphone("Tank Temp over 80F", "start to panic");
      char tempdata[20];
      sprintf (tempdata, "The Tank temp is: %d.%.2d", Tanktemp_first, Tanktemp_second); 
      Serial.println(tempdata);

      //Send_message_to_iphone(tempdata, " Level 1 - Turned off Main Lights");
      Over_temp_Level_1_message_sent = true;
      //heroku_in_out();
    }

 

  }
  else{
   
    Over_temp_Level_1_message_sent = false; 

  }


  if(tempF_Overtime > Level_2_Overtemp){

    // Level 2 of the Overtemp Correct Plan in use

    if(Over_temp_Level_2_message_sent == false){

      int Tanktemp_first = tempF_Overtime; ////  makes 26.7 into 26
      int TempF2 = tempF_Overtime * 100;////  makes 26.7 into 2670
      int TempF3 = Tanktemp_first * 100; /// makes 26 into 2600
      int Tanktemp_second = TempF2 - TempF3;
      // heroku_in_out();
      ////Send_message_to_iphone("Tank Temp over 80F", "start to panic");
      char tempdata[20];
      sprintf (tempdata, "The Tank temp is: %d.%.2d", Tanktemp_first, Tanktemp_second); 
      Serial.println(tempdata);

      //Send_message_to_iphone(tempdata, "Level 2 - Cycling ATS pump");
      Over_temp_Level_2_message_sent = true;
      //heroku_in_out();
    }



 

  }
  else{

 
    Over_temp_Level_2_message_sent = false; 

  }


  if(tempF_Overtime > Level_3_Overtemp){

    // Level 3 of the Overtemp Correct Plan in use

    if(Over_temp_Level_3_message_sent == false){

      int Tanktemp_first = tempF_Overtime; ////  makes 26.7 into 26
      int TempF2 = tempF_Overtime * 100;////  makes 26.7 into 2670
      int TempF3 = Tanktemp_first * 100; /// makes 26 into 2600
      int Tanktemp_second = TempF2 - TempF3;
      // heroku_in_out();
      ////Send_message_to_iphone("Tank Temp over 80F", "start to panic");
      char tempdata[20];
      sprintf (tempdata, "The Tank temp is: %d.%.2d", Tanktemp_first, Tanktemp_second); 
      Serial.println(tempdata);

      //Send_message_to_iphone(tempdata, "Level 3 - Turned off PowerHead");
      Over_temp_Level_3_message_sent = true;
      //heroku_in_out();
    }


    disablepowerhead = true;



  }
  else{

    disablepowerhead = false;
    Over_temp_Level_3_message_sent = false; 

  }



}





