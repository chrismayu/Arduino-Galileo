void Voltage_Detected_Where(){

// hi
  //turn off each electrical device and check

  // turn off   Heater  & Check
  if(Found_Voltage_Problem == false){

    digitalWrite(Heater, HIGH);
    delay(200);

    //check for voltage
    //sensorValue = sensor.getAverage(10);

    if(Voltage_detect == true){
      //not heater so turn back on
      digitalWrite(Heater, LOW);

    }
    else{
      // heater is the problem
      disableheater = true;
      Found_Voltage_Problem = true;
      // send error code to iphone and display in screens
      if(Found_Voltage_Problem_iphone_sent == false){
        //Send_message_to_iphone("Heater is leaking", "I have turned it off Please help me");
        Found_Voltage_Problem_iphone_sent == true;
      }
    }

  }


  // turn off Main Pump and check
  if(Found_Voltage_Problem == false){

    //digitalWrite(Main_Pump, HIGH);
    delay(200);

    //check for voltage
    if(Voltage_detect == true){
      //not MainPump so turn back on
      //digitalWrite(Main_Pump, LOW);

    }
    else{
      // MainPump is the problem
      disablemainpump = true;
      Found_Voltage_Problem = true;
      // send error code to iphone and display in screens}
      if(Found_Voltage_Problem_iphone_sent == false){
        //Send_message_to_iphone("Main Pump is leaking ","I have turned it off  Please help me");
        Found_Voltage_Problem_iphone_sent = true;
      }
    }
  }

  // Turn off Powerhead and check
  if(Found_Voltage_Problem == false){

    digitalWrite(PowerHead, HIGH);
    delay(200);

    //check for voltage
    if(Voltage_detect == true){
      //not Powerhead so turn back on
      digitalWrite(PowerHead, LOW);

    }
    else{
      // Powerhead is the problem
      disablepowerhead = true;
      Found_Voltage_Problem = true;
      // send error code to iphone and display in screens}

      if(Found_Voltage_Problem_iphone_sent == false){
        //Send_message_to_iphone("The Powerhead is leaking Voltage","I Have turned it off  Please help me");
        Found_Voltage_Problem_iphone_sent = true;
      }
    }
  }

  //Turn off chiller and check
  if(Found_Voltage_Problem == false){

    //digitalWrite(Chiller, HIGH);
    delay(200);

    //check for voltage
    if(Voltage_detect == true){
      //not chiller so turn back on
     // digitalWrite(Chiller, LOW);

    }
    else{
      // chiller is the problem
      disablechiller = true;
      Found_Voltage_Problem = true;
      // send error code to iphone and display in screens}
      if(Found_Voltage_Problem_iphone_sent == false){
        //Send_message_to_iphone("The chiller is leaking ","I have turned it off  Please help me");
        Found_Voltage_Problem_iphone_sent = true;
      }

    }
  }


  //turn off main light and check
  if(Found_Voltage_Problem == false){

 
    delay(200);

    //check for voltage
    if(Voltage_detect == true){
      //not v so turn back on
    

    }
    else{
      // chiller is the problem
 
      Found_Voltage_Problem = true;
      // send error code to iphone and display in screens}
      if(Found_Voltage_Problem_iphone_sent == false){
        //Send_message_to_iphone("The Main Lights are leaking ","I have turned it off  Please help me");
        Found_Voltage_Problem_iphone_sent = true;
      }

    }
  }



  //turn off refuge lights and check

  if(Found_Voltage_Problem == false){

    digitalWrite(RefugeLED, HIGH);
    delay(200);

    //check for voltage
    if(Voltage_detect == true){
      //not v so turn back on
      digitalWrite(RefugeLED, LOW);

    }
    else{
      // chiller is the problem
      disablerefugelight = true;
      Found_Voltage_Problem = true;
      // send error code to iphone and display in screens}

      if(Found_Voltage_Problem_iphone_sent == false){
        //Send_message_to_iphone("The Refuge lights are leaking Voltage","I have turned it off  Please help me");
        Found_Voltage_Problem_iphone_sent = true;
      }
    }
  }


 // turn off   ATS  & Check
  if(Found_Voltage_Problem == false){

 
    delay(200);

    //check for voltage
    //sensorValue = sensor.getAverage(10);

    if(Voltage_detect == true){
      //not heater so turn back on
 

    }
    else{
      // heater is the problem
 
      Found_Voltage_Problem = true;
      // send error code to iphone and display in screens
      if(Found_Voltage_Problem_iphone_sent == false){
        //Send_message_to_iphone("ATS Pump is leaking", "I have turned it off Please help me");
        Found_Voltage_Problem_iphone_sent == true;
      }
    }

  }


}





// reset the Found_Voltage_Problem bit somewhere


void Reset_Voltage_Fault(){

  //LCD.Clear();
  //LCD.GotoXY(0,3);
  //LCD.print("Resetting all alarms and systems");

  // reset all outputs
  disableheater = false;
  disablemainpump = false;
  disablepowerhead = false;
  disablechiller = false;
 
  disablerefugelight = false;
  
  // reset GFCI Fault
  GFCI_tripped_iphone_sent = false;

  // reset "Found_Voltage_Problem"
  Found_Voltage_Problem =  false;
  Found_Voltage_Problem_iphone_sent = false;

  // run voltage check again here
  //check_for_Voltage();

  // add reset for feeding mode and waterchange. ato
  if (checklevel_ATOrunning == 1){
    checklevel_ATOrunning = 0; //turn off ATO mode
    checklevel_ATO = 3;

  }

  if (waterchangemoderunning == 1){
    waterchangemoderunning = 0; //turn off waterchange mode

  }

  if (feedmoderunning == 1){
    feedmode = 3; //turn off feeding mode
  }

  delay(800);
  //LCD.Clear();
}


void check_for_Voltage(){

  if (check_voltage_now == true){
    /*
  // read the analog in value:
     
     //--  VoltValue = analogRead(analogInPin); 
     // Voltage sensor measures from -30v to 30v with the resolution on the Arduino of 0-1024
     // Volt sensor only has a range of .5v -4.5v making it 10-922, instead of 0-1024
     // 922-512 = 410 & 30v /410 =~.073 Volts per unit
     // 60 / 1024
     //--  Voltage = (VoltValue - 512) * 0.073170;
     
     // of Voltage is greater then 2 volts fault out
     if ( Voltage >= 2){
     // make alarm
     // run check where program
     
     }
     
     
     // print the results to the serial monitor:
     Serial.print("Volts Sensor Reading: ");
     Serial.println(VoltValue);      
     Serial.print("Voltage Reading: ");
     Serial.println(Voltage);      
     */
    check_voltage_now = false;

  }

  // move time into int

  // if time is different  then run

  if (RTC.second !=  Voltage_lastchecked){
    check_voltage_now = true;

    Voltage_lastchecked = RTC.second;
  }


}


void checkGFCI(){
  // add send to iphone message




  if(bottom_relays.digitalRead(GCFI_Monitoring) == LOW) {
    //LCD.Clear();
    GFCI_tripped = true;
     if(GFCI_tripped_iphone_sent == false){
        //Send_message_to_iphone("GCFI has Tripped", " Please help me");
         GFCI_tripped_iphone_sent == true;
      }
    
    Serial.print("Stating While loop");
    if (bottom_relays.digitalRead(GCFI_Monitoring) == LOW) {
      Serial.print("Inside While loop");
      //LCD.GotoXY(0,1);
      //LCD.print("GCFI Has been Tripped  Please Reset");
      //LCD.GotoXY(0,3);
      //LCD.print("!!!!Please Reset!!!!");
      //LCD.GotoXY(0,5);
      //LCD.print("Just sent a message to: Chris' iPhone");
      //LCD.GotoXY(0,6);
      //LCD.print("Chris' iPhone");
      
      //LCDsmall.setCursor(0, 0);
      //LCDsmall.print("GCFI Has been Tripped ");  //
      //LCDsmall.setCursor(0, 1);
      //LCDsmall.print("!!!!Please Reset!!!!");
    }
  }
  else{
      Serial.print("Entering Else Statement");
    if(GFCI_tripped == true) {
      //LCD.Clear();
      GFCI_tripped = false;
      GFCI_tripped_iphone_sent = false;
    }
  }




}



