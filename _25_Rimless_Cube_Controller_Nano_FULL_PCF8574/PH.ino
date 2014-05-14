/*
void TestPH(){

  digitalWrite(Grounding_plug, HIGH); /// turn off grounding probe
  delay(500);

  byte holding;
  char data[12];  
  Serial3.flush();

  // ph stamp a new command
  if(TanktempC > 0)
  {

    int T = TanktempC * 100;  // 26.50 x 100   =  2650 
    int L = T / 100;  //  2650 / 100 = 26 
    int R = T - (L * 100);
    Serial.print ("I am going to send the PH Stamp Rob's Logic: " ); 



    sprintf(PH_Temp_data,"%d.%.2d", L, R);

    Serial.print ("Sprint : " ); 
    Serial.println(PH_Temp_data);
    Serial.print("new float:");
    Serial.println(TanktempC, 2);

    // Serial3.print(PH_Temp_data);  // send temperature 
    Serial3.print(TanktempC, 2);  // send temperature 
    Serial3.print(13, BYTE); // end 
  } 
  else 
  { 
    Serial3.print("r");  // send "r" 
    Serial3.print(13, BYTE); // end 
  }

  /*
  // ph stamp a new command
   if(TanktempC > 0)
   {
   // temperatur sensor nicht angeschlossen
   Serial3.print(TanktempC, DEC);  // send temperatur or "r". nicht beides!
   Serial3.print(13, BYTE); // ende
   }
   else
   {
   Serial3.print("r");  // send temperatur or "r". nicht beides!
   Serial3.print(13, BYTE); // ende
   }
   
   */  /*
  delay(550);
  if(keypadmode == Temp_Screen){
    // //LCD.setCursor(0, 2);
    // //LCD.print("PH ");

  }
  holding=Serial3.available();            //lets read how many bytes have been received
  // byte holding=Serial3.available();            //lets read how many bytes have been received

#ifdef DEBUG
  Serial << _DEC(holding) << " byte received from PH stamp" << endl;
#endif

  if(holding > 4 && holding <=12) {  //if we see the more than three bytes have been received by the Arduino
    // char data[12];          //this is where the data from the stamp is stored. if no pH probe is connected, the message "check probe" ansmitted.
      for(byte i=0; i <= holding-1;i++) {  //we make a loop that will read each byte we received
      data[i]= char(Serial3.read());     //and load that byte into the stamp_data array
    }
#ifdef DEBUG
    Serial.print("PH=");
    for(byte i=0; i <= holding-1;i++) {  //we now loop through the array
      Serial.print(data[i]);             //printing each byte we received  through the hardware UART
    }
    Serial.println(""); 
#endif

    if (atoi(data) != 0) {
      pHValue = atof(data);
    }
    else {
      pHValue = 0;
    }

    if(pHValue > 0) {

      // calPHValue = pHValue + pHCalibrationValue;


    }
    else{
    }

    // PHerror = 0;

  }
  else if(holding == 0)
  {
    PHerror = 1;
    Serial.println("Error: No data from PH probe");
  }
  else if(holding > 12)
  {
    PHerror = 2;
    Serial.println("Error: Too many data from PH probe. Max 12 is allowed.");
  }

  if(pHValue > 0.0 )
  {
    calPHValue = pHValue + pHCalibrationValue;
    //calPHValue = calPHValue - pHCalibrationValue;
    Serial.println("Updated PH valve  *******************************************");
    Serial.print("calPHValue:");
    Serial.println(calPHValue);
    Serial.print("pHCalibrationValue:");
    Serial.println(pHCalibrationValue);
    Serial.print("PHValue:");
    Serial.println(pHValue);
  }
  if(pHValue > 0.0 )
  {
    // Alarm beim PH Sensor
    if(calPHValue <= pHMinAlarm || calPHValue >= pHMaxAlarm)
    {
      //Alarm("Check PH Value");
/*
      if(PH_Problem_message_sent == false){
        Serial.println("tank has PH Problem  send iphone message *******************************************");
        // add what the PH i
        int PH_first = calPHValue; ////  makes 26.7 into 26
        int PH2a = calPHValue * 100;////  makes 26.7 into 2670
        int PH3a = PH_first * 100; /// makes 26 into 2600
        int PH_second = PH2a - PH3a;

        int wholeTempC = calPHValue; // The whole part
        int fracTempC = (calPHValue - wholeTempC) * 100; // The fractional part * 1000 


          char tempdata[20];
        sprintf (tempdata, "The PH is: %d.%.2d", PH_first, PH_second); 
        Serial.println(tempdata);

        RTC.getTime();


        if (hourlastsent != RTC.hour)
        {
         //Send_message_to_iphone(tempdata, "just wanted to let you know");
          hourlastsent = RTC.hour;

        }
        else{

        }

        /////Send_message_to_iphone(tempdata, "just wanted to let you know");
        PH_Problem_message_sent = true;
       // heroku_in_out();


      }
      else{

      }

*/ /*
    }
    // else
    ClearAlarmMessage();
    
   // PH_Problem_message_sent = false; 



    // CO2 einschalten oder ausschalten
    if(pHValue >= pHMax) {
#ifdef DEBUG
      Serial << "PH >= " << pHMax << endl;
#endif
      digitalWrite(relayPin1, LOW); // LOW ist einschlten!
    }
    else if(pHValue <= pHMin) {
#ifdef DEBUG
      Serial << "PH <= " << pHMin << endl;
#endif
      digitalWrite(relayPin1, HIGH); // HIGH ist ausschlten!
    }
    else
      digitalWrite(relayPin1, HIGH);
  }
  Serial3.flush();


  // create Time Stamp for Display
  RTC.getTime();

  sprintf(PHtext, "   %02d:%02d:%02d", RTC.hour, RTC.minute, RTC.second);

  if (hourlastsent != RTC.hour)
  {

    hourlastsent = RTC.hour;

  }
  else{

  }


  digitalWrite(Grounding_plug, LOW); /// turn on grounding probe


 if(keypadmode == PH_Screen){
     //LCD.Clear();
 }

}

*/


void printPH()
{
  
  /*
  //  Serial.print("calPHValue:");
  //  Serial.println(calPHValue);
  // Serial.print("PHValue:");
  // Serial.println(pHValue);
  if(calPHValue <= 3){
    if((RTC.second) == 10 || RTC.second == 15){

      TestPH(); 
    }

  }



  if(RTC.minute == 0 || RTC.minute == 5 || RTC.minute == 10 || RTC.minute == 15 || RTC.minute == 20 || RTC.minute == 25 || RTC.minute == 30 || RTC.minute == 35 || RTC.minute == 40 || RTC.minute == 45 || RTC.minute == 50 || RTC.minute == 55){
    if((RTC.second) == 10){

      TestPH(); 
    }
  }



  if(keypadmode == PH_Screen){
    //LCD.setCursor(0, 2);
    //LCD.print("PH: ");
    //LCD.setCursor(4, 2);
    // //LCD.print("PH ");
    //LCD << _FLOAT(calPHValue, 2) << " ";

    //LCD.setCursor(0, 3);
    if(PHerror == 1){
      //LCD.print("Er: Check Probe");
    }
    if(PHerror == 2){
      //LCD.print("Er: Check PHStamp");
    }

    //LCD.setCursor(0, 4);
    //LCD.print("Temp Send:");
    //LCD.setCursor(0, 5);
    // //LCD.print(PH_Temp_data);

    //LCD.print(TanktempC, 2);  
    //LCD.setCursor(0, 6);
    //LCD.print("Time Stamp:");
    //LCD.setCursor(0, 7);
    //LCD.print(PHtext);
  }


  if(small_LCD_Screen == S_L_PH_Screen){

    //LCDsmall.setCursor(0, 1);
    //LCDsmall.print("PH: ");
    //LCDsmall.setCursor(4, 1);
    //LCDsmall << _FLOAT(calPHValue, 2) << "         ";
  }




  PH_heroku = calPHValue;


  if(PH_heroku != PH_heroku_AVG){

    int PH_heroku_transfer = PH_heroku * 100;
    Serial.print("PH_heroku_transfer");
    Serial.println(PH_heroku_transfer);
    // PH Average *******************  // subtract the last reading:
    PH_Avg_total= PH_Avg_total - PH_Avg_readings[PH_Avg_index];          
    // read from the sensor:  
    PH_Avg_readings[PH_Avg_index] = PH_heroku_transfer;  // add the reading to the total:
    PH_Avg_total= PH_Avg_total + PH_Avg_readings[PH_Avg_index];        // advance to the next position in the array:  
    PH_Avg_index = PH_Avg_index + 1;                    


    if (PH_Avg_index_2 < PH_Avg_numReadings)  {             
      PH_Avg_index_2 = PH_Avg_index_2 + 1;         
    }    
    else{
    }            

    // if we're at the end of the array...
    if (PH_Avg_index >= PH_Avg_numReadings)   {           
      // ...wrap around to the beginning:  
      PH_Avg_index = 0;      
    }    
    else{
    }                   // calculate the average:
    float PH_Avg_average_0 = PH_Avg_total / PH_Avg_index_2;          // send it to the computer as ASCII digits
    Serial.print("PH_Avg_total: ");
    Serial.println(PH_Avg_total);
    Serial.print("PH_Avg_index_2: ");
    Serial.println(PH_Avg_index_2);
    Serial.print("PH_Avg_average_0: ");
    Serial.println(PH_Avg_average_0);


    PH_Avg_average = PH_Avg_average_0 / 100;

    Serial.print("PH_Avg_average");
    Serial.println(PH_Avg_average);
    PH_heroku_AVG = PH_heroku;



  }


*/
} 









