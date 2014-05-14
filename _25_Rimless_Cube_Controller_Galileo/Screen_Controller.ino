void Small_LCD_Controller(){
  
  // used to cycle small //LCD screen
  
   RTC.getTime();
  
  if(RTC.second == 0 || RTC.second == 5 || RTC.second == 10 || RTC.second == 15 || RTC.second == 20 || RTC.second == 25 || RTC.second == 30 || RTC.second == 35 || RTC.second == 40 || RTC.second == 45 || RTC.second == 50 || RTC.second == 55){
  //  Serial.print("trying to update");
    if(S_L_Screen_Updated == false){
    
   small_LCD_Screen += 1;
    }
    
 if(small_LCD_Screen == return_to_first_screen){
 small_LCD_Screen = 1;
 }
 S_L_Screen_Updated = true;
 
  }else{
    
    
     S_L_Screen_Updated = false;
    
  }
 // Serial.print(S_L_Screen_Updated);
 // Serial.print(small_LCD_Screen);
}
