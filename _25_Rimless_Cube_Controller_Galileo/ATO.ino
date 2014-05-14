/****************Auto top off********************************************************************************/
void ATO(){ /// Main ATO Program Controller



  if(RTC.hour == 8 && RTC.minute == 8){

    ATO_Fault_Count = 0;
    ATO_lenght_of_run = 0;
    Watchman_timer_ATO_AT = 0;
    Ato_okay_to_run_now = 0;
    Ato_Pump_last_ran = 0;
    Ato_okay_to_run_pump_now = 0;
  }


  if(current_time >= ATO_Master_On && current_time <= ATO_Master_Off){


    if(RTC.hour == 10 || RTC.hour == 12 || RTC.hour == 14 || RTC.hour == 16 || RTC.hour == 18 || RTC.hour == 20 || RTC.hour == 22 ){

      ATO2();

    }
    else{

      bottom_relays.digitalWrite(ATO_Valve, HIGH); // turn off ATO Pump
    }



  }
  else{

    bottom_relays.digitalWrite(ATO_Valve, HIGH); // turn off ATO Pump
  }


}





void ATO2(){ /// Main ATO Program Controller

//  Serial.print("-----  ATO Start ---------- ");

  //Delcarations


  float time_Fault;
  float start_time;
  boolean pump_is_running;


  ATO_delay_between_runs = 0.05;

  ATO_delay_lenght_of_run = 0.05;

  Run_Pump_for_only_timer = 0.03;

  if(bottom_relays.digitalRead(ATO_Valve) == HIGH ){
    pump_is_running = false;

  }

  else{
    pump_is_running = true;

  }


  if(bottom_relays.digitalRead(ATO_High) == HIGH ){



    current_status_of_water_level = true; //WaterLevel okay

    ATO_Run_Next_Time = HIGH;

    // Serial.println( "LEVEL IS LOW");

    S_L_ATO_Screen_text = "H20 Low Run ATO ";

  } 
  else{

    current_status_of_water_level = false;

    bottom_relays.digitalWrite(ATO_Valve, HIGH); // turn off ATO Pump

    ATO_Run_Next_Time = LOW;

    S_L_ATO_Screen_text = "H20 Level = Fine ";

    //Serial.println( "LEVEL IS FINE");

    Reset_ATO_Fault(); // reset All faults if water level is fine

  }




  // adds a delay between runnings If Water Level is high- so it isn't starting and stopping

  float ATO_delay_Water_level = ATO_delay_between_runs + ATO_ran_last;

  if(ATO_delay_Water_level >= Ato_okay_to_run_now && start_delay_for_filled_timmer == false && pump_is_running == false){
    Serial.println("  ");
    Serial.println("Added Delay after reaching correct water level");
    Serial.print("ATO_delay_Water_level ");
    Serial.println(ATO_delay_Water_level);
    Serial.println(" ");
    Ato_okay_to_run_now = ATO_delay_Water_level;
    start_delay_for_filled_timmer = true;

  }


  if(pump_is_running == High ){

    // Pump is ON

    /// Screen Display Data

    sprintf(Last_ATO, "ATO RAN: %02d/%02d %02d:%02d", RTC.month, RTC.day, RTC.hour, RTC.minute);

    S_L_ATO_LAST_Screen_text = "ATO PUMP Running";


    Watchman_timer_ATO_AT = Started_ATO + Run_Pump_for_only_timer;



    if(Watchman_timer_ATO_AT >= current_time){

      float Watchman_timer_ATO_AT_timer = ATO_delay_between_runs + current_time;

      if(Watchman_timer_ATO_AT_timer >= Ato_okay_to_run_now){

     //   Serial.println("Added Delay for watcher timer");
      //  Serial.print("Watchman_timer_ATO_AT_timer ");
      //  Serial.println(Watchman_timer_ATO_AT_timer);
      //  Serial.println(" ");

        Ato_okay_to_run_now = Watchman_timer_ATO_AT_timer;

        ATO_Fault_Count = ATO_Fault_Count + 1;

      }
    }

    ATO_ran_last = current_time;

  }
  else{

    // Pump is OFF
    start_delay_for_filled_timmer = false;
    Started_ATO = current_time;
  }


  /// ATO Pump Start/Stop Logic

  if(current_time >= Ato_okay_to_run_now && ATO_Run_Next_Time == HIGH){ // && ATOfaulted == LOW){

    Serial.println("ATO Pump Running");

    bottom_relays.digitalWrite(ATO_Valve, LOW); //turn ON ATO Pump

  }
  else{

    bottom_relays.digitalWrite(ATO_Valve, HIGH); // Turn OFF Pump

  }

/*
  Serial.print("ATO_Fault_Count: ");   
  Serial.println(ATO_Fault_Count);

  Serial.print("Ato_okay_to_run_now ");
  Serial.println(Ato_okay_to_run_now);

  Serial.print("Current Time ");
  Serial.println(current_time);



  Serial.print("Will Run in: ");

  Serial.println(current_time - Ato_okay_to_run_now);

  Serial.print("ATO_ran_last ");

  Serial.println(ATO_ran_last);



  Serial.print("Water Level ");

  Serial.println(current_status_of_water_level);



  Serial.print("ATO_Run_Next_Time ");

  Serial.println(ATO_Run_Next_Time);



  Serial.print("ATO_Got_Time ");

  Serial.println(ATO_Got_Time);

  Serial.print(" ");

  Serial.print("-----  ATO END ---------- ");


*/




  /// Fault Logic





  if(ATO_Fault_Count >= 3){

    ATOfaulted = HIGH;

    Fault_meessage_to_Reef_Sense();

  } 
  else{
    sent_ato_fault_message_to_iphone = LOW;
  }
}


void Screen_ATO(){

  //could move this to screen tab

  // First ATO Screen



  if(small_LCD_Screen == S_L_ATO_Screen){

    //LCDsmall.setCursor(0, 1);

    //LCDsmall.print(S_L_ATO_Screen_text);

  }


  //Second ATO Screen



    if(small_LCD_Screen == S_L_ATO_LAST_Screen){

    //LCDsmall.setCursor(0, 1);

    //LCDsmall.print(S_L_ATO_LAST_Screen_text);

  }





}







void Reset_ATO_Fault(){

  ATO_Fault_Count = 0;

  ATOfaulted = LOW;



}





void Fault_meessage_to_Reef_Sense(){





  if (sent_ato_fault_message_to_iphone == LOW){



    //Send_message_to_Reef_Sense("ATO System", " Faulted - Check RO Water Supply");



    sent_ato_fault_message_to_iphone = HIGH;

  }





}







