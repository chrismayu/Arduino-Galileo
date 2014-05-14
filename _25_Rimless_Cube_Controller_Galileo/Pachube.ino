

void status_of_heroku_info(){



  boolean go_ahead_push_to_heroku;

  

  go_ahead_push_to_heroku = false;

  



  if( bottom_relays.digitalRead(Main_Pump) == LOW){

    current_status_of_Main_Pump = true;

    }

    else{

    current_status_of_Main_Pump = false;

    }



  if( bottom_relays.digitalRead(PowerHead) == LOW){

    current_status_of_PowerHead = true;

    }

    else{

    current_status_of_PowerHead = false;

    }



  if( bottom_relays.digitalRead(Heater) == LOW){

    current_status_of_Heater = true;

    }

    else{

    current_status_of_Heater = false;

    }

    
 



  if(top_relays.digitalRead(RefugeLED) == LOW){

    current_status_of_RefugeLED = true;

    }

    else{

    current_status_of_RefugeLED = false;

    }

 



  if( bottom_relays.digitalRead(Skimmer) == LOW){

    current_status_of_Skimmer = true;

    }

    else{

    current_status_of_Skimmer = false;

    }

   

 

    

  if( bottom_relays.digitalRead(ATO_Valve) == LOW){

    current_status_of_ato_valve = true;

    }

    else{

    current_status_of_ato_valve = false;

    }

  

  if(pass_status_of_ato_valve != current_status_of_ato_valve){

  //  Serial.println("check status - ato");

      go_ahead_push_to_heroku = true;

      if (current_status_of_ato_valve == true){

      



      heroku_code = "01";  // ON





     }else{



      heroku_code = "41";  // OFF



      }

    pass_status_of_ato_valve = current_status_of_ato_valve;

    }

    

   if(pass_status_of_Main_Pump != current_status_of_Main_Pump){

    // Serial.println("check status - main pump");

        go_ahead_push_to_heroku = true;

      if (current_status_of_Main_Pump == true){

      



      heroku_code = "02";  // ON





     }else{



      heroku_code = "42";  // OFF



      }

    pass_status_of_Main_Pump = current_status_of_Main_Pump;

    }

    

     if(pass_status_of_PowerHead != current_status_of_PowerHead){

     //  Serial.println("check status - powerhead");

        go_ahead_push_to_heroku = true;





      if (current_status_of_PowerHead == true){

      



      heroku_code = "03";  // ON





     }else{



      heroku_code = "43";  // OFF



      }





    

    pass_status_of_PowerHead = current_status_of_PowerHead;

    }

    

     if(pass_status_of_Heater != current_status_of_Heater){

      // Serial.println("check status - heater");

        go_ahead_push_to_heroku = true;



      if (current_status_of_Heater == true){

      



      heroku_code = "04";  // ON





     }else{



      heroku_code = "44";  // OFF



      }





      

    pass_status_of_Heater = current_status_of_Heater;

    }

    

     if(pass_status_of_Chiller != current_status_of_Chiller){

        go_ahead_push_to_heroku = true;



      if (current_status_of_Chiller == true){

      



      heroku_code = "05";  // ON





     }else{



      heroku_code = "45";  // OFF



      }





       

    pass_status_of_Chiller = current_status_of_Chiller;

    }

  

     if(pass_status_of_RefugeLED != current_status_of_RefugeLED){

       Serial.println("check status - Refuge LED");

      go_ahead_push_to_heroku = true;



      if (current_status_of_RefugeLED == true){

      



      heroku_code = "06";  // ON





     }else{



      heroku_code = "46";  // OFF



      }





    pass_status_of_RefugeLED = current_status_of_RefugeLED;

    }

    



     if(pass_status_of_Skimmer != current_status_of_Skimmer){

    

      go_ahead_push_to_heroku = true;

      if (current_status_of_Skimmer == true){

      



      heroku_code = "15";  // ON





     }else{



      heroku_code = "55";  // OFF



      }

    pass_status_of_Skimmer = current_status_of_Skimmer;

    }

    



 

  

  if(Tank_Temp_Avg_average != tempF2_heroku){

  

     Tank_tempF_heroku_2 = (DallasTemperature::toFahrenheit(Tank_Temp_Avg_average));

 

   

   if(Tank_tempF_heroku_2 > 40){

    

     Serial.print("Temp F told heroku to work: ");

  

       go_ahead_push_to_heroku = true;

       heroku_code = "07";

   }else{

   

   }

 

 

  tempF2_heroku = Tank_Temp_Avg_average;

  //Serial.print(Tanktemp_first_heroku); Serial.print(".");

 // Serial.println(Tanktemp_second_heroku);

}



 



Ambient_tempF_heroku = (DallasTemperature::toFahrenheit(AmbienttempC));



 if(Ambient_tempF_heroku != Ambient_tempF2_heroku){

  

float Ambient_tempF_heroku_1 = Ambient_Temp_Avg_average;

 Ambient_tempF_heroku_2 = (DallasTemperature::toFahrenheit(Ambient_tempF_heroku_1));



  Ambienttemp_first_heroku = Ambient_tempF_heroku_2; //// makes 26.7 into 26

 int Ambient_tempF2 = Ambient_tempF_heroku_2 * 100;//// makes 26.7 into 2670

 int Ambient_tempF3 = Ambienttemp_first_heroku * 100; /// makes 26 into 2600

   Ambienttemp_second_heroku = Ambient_tempF2 - Ambient_tempF3;

   

    if(Ambienttemp_first_heroku > 40){

    Serial.print(" Ambient Temp F told heroku to work: ");

    // go_ahead_push_to_heroku = true;

     // heroku_code = "08";

   }else{

   

   }





  Ambient_tempF2_heroku = Ambient_tempF_heroku;

  

   

}



  if(Tank_tempF_heroku_2 > 20)

  {

    temps_up = true;

    // Serial.print("heroku set to true");

  }



 if(go_ahead_push_to_heroku == true && temps_up == true){

   Serial.print("Status of Heroku told Arduino to push data");

     heroku_in_out();

   }







}













void heroku_in_out() {

   Serial.println("Going to TRY to send data");



  digitalWrite(Grounding_plug, HIGH); /// turn off grounding probe

 delay(500);

    

 

    char main_temp[10];

    String main_tempAsString;

    dtostrf(Tank_tempF_heroku_2,1,2,main_temp);

    main_tempAsString = String(main_temp);

 

    char Ambient_temp[10];

    String Ambient_tempAsString;

    dtostrf(Ambient_tempF_heroku_2,1,2,Ambient_temp);

    Ambient_tempAsString = String(Ambient_temp);



  String ato_valve;

    if(current_status_of_ato_valve == true){

    ato_valve = "T";

    }

    else{

    ato_valve = "F";

    }

    

     String water_level;

    if(current_status_of_water_level == true){

    water_level = "T";

    }

    else{

    water_level = "F";

    }



   String powerhead;

    if(current_status_of_PowerHead == true){

    powerhead = "T";

    }

    else{

    powerhead = "F";

    }

     

    

     String heater;

    if(current_status_of_Heater == true){

    heater = "T";

    }

    else{

    heater = "F";

    }

    

     String main_pump;

    if(current_status_of_Main_Pump == true){

    main_pump = "T";

    }

    else{

    main_pump = "F";

    }

    



     String skimmer;

    if(current_status_of_Skimmer == true){

    skimmer = "T";

    }

    else{

    skimmer = "F";

    }



  //    \"skim\":\"" + skimmer + "\",

    

          String refuge_led;

    if(current_status_of_RefugeLED == true){

    refuge_led = "T";

    }

    else{

    refuge_led = "F";

    }        



  //    \"r_l\":\"" + refuge_led + "\",  

   

   

 String data = "{\"m_t\":\"" + main_tempAsString + "\", \"t_n\":\"" + arduino_reef_tank_id + "\", \"a_t\":\"" + Ambient_tempAsString + "\",\"w_l\":\"" + water_level + "\", \"r_l\":\"" + refuge_led + "\", \"skim\":\"" + skimmer + "\", \"ph\":\"" + powerhead + "\", \"m_p\":\"" + main_pump + "\", \"h\":\"" + heater + "\", \"h_c\":\"" + heroku_code + "\", \"ato\":\"" + ato_valve + "\"}";

 

// Serial.print("Data to Send: ");

// Serial.println(data);

 

sendData(data); /// Send Data to Heroku

 

digitalWrite(Grounding_plug, LOW); /// turn off grounding probe





   heroku_code = "00";  ///clear the code for next time

}















// this method makes a HTTP connection to the server:
void sendData(String thisData) {
  
  String uri = ("/watchers");
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    
    
    Serial.println("start sending data");
  client.print("POST ");
  client.print(uri);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(heroku_url);
 
   client.println("Content-Type: application/json");
  //client.println("Content-Type: application/x-www-form-urlencoded");
  client.println("Connection: close");
  client.print("Content-Length: ");
  client.println(thisData.length());
  client.println();
   Serial.print("data:-----");
 Serial.println(thisData);
  client.print(thisData);
  client.println();
  Serial.println("done sending data");
    
 last_connection_sent = true;
   
  failures = 0;
     
  } 
  else {
    // if you couldn't make a connection:
    last_connection_sent = false;
      
    failures = failures + 1;
    Serial.println("connection failed");
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
  // note the time that the connection was made or attempted:
  lastConnectionTime = millis();
}



 

void Maintain_heroku_connection(){
  
  
 RTC.getTime();

 if(RTC.minute == 10 || RTC.minute == 40){
  if(Maintain_connection_sent == false){
    
    printDate();
   Serial.print("Send data to heroku to maintain connection");
    heroku_code = "11";
   heroku_in_out();
  
   Maintain_connection_sent = true; 
 
  } 
  }else{
   Maintain_connection_sent = false;
   
}

if(last_connection_sent == false && failures > 4){
  Serial.println("Failed Last time  - Trying to send again...........");
  heroku_code = "12";
  heroku_in_out();
  
  
}






}

void heroku_Screen_controls(){
  // put screen stuff here

 if(keypadmode == heroku_Screen){
    //LCD.setCursor(0, 3);
    //LCD.print("Status: ");
    //LCD.setCursor(8, 4);
if(last_connection_sent == false){
  //LCD.print("Failed");
}else{
//LCD.print("Okay");
}
   //LCD.setCursor(0, 5);
    if(Maintain_connection_sent == false){
  //LCD.print("Maintained: F");
}else{
//LCD.print("Maintained: T");
}
   
    
    //LCD.setCursor(0, 6);
    //LCD.print("Last Trans:");
    //LCD.setCursor(0, 7);
    //LCD.print(herokutext);
  }

  
  
if(small_LCD_Screen == S_L_heroku_Screen){
 
    
   //LCDsmall.setCursor(0, 1);
 if(last_connection_sent == false){
   
   //LCDsmall.print("Pach:NG ");

}else{
 //LCDsmall.print("Pach:OK ");
}
 

    //LCDsmall.setCursor(8, 1);
    //LCDsmall.print("LS:");
   //LCDsmall. print(herokutext_small_//LCD);
}


  
  
}
