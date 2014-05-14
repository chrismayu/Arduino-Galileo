 

boolean debounce99(boolean last)
{
  boolean current = buttons.digitalRead(mode99pb);
  if (last != current)
  {
    delay(5);
    current = buttons.digitalRead(mode99pb);
  }
  return current;
}

boolean debounce100(boolean last)
{
  boolean current = buttons.digitalRead(Shelf_Light_PB);
  if (last != current)
  {
    delay(5);
    current = buttons.digitalRead(Shelf_Light_PB);
  }
  return current;
}

boolean debounce101(boolean last)
{
  boolean current = buttons.digitalRead(Feeding_Mode_PB);
  if (last != current)
  {
    delay(5);
    current = buttons.digitalRead(Feeding_Mode_PB);
  }
  return current;
}
boolean debounce102(boolean last)
{
  boolean current = buttons.digitalRead(WaterChange_Mode_PB);
  if (last != current)
  {
    delay(5);
    current = buttons.digitalRead(WaterChange_Mode_PB);
  }
  return current;
}

boolean debounce103(boolean last)
{
  boolean current = buttons.digitalRead(mode103pb);
  if (last != current)
  {
    delay(5);
    current = buttons.digitalRead(mode103pb);
  }
  return current;
}

boolean debounce104(boolean last)
{
  boolean current = buttons.digitalRead(mode104pb);
  if (last != current)
  {
    delay(5);
    current = buttons.digitalRead(mode104pb);
  }
  return current;
}

 

void checkmode()
{
 


  //int mode = 100;
 // Serial.println("99");

  currentButton99 = debounce99(lastButton99);
  if (lastButton99 == HIGH && currentButton99 == LOW)
  {
    
    Reset_ATO_Fault();
 
  }

  lastButton99 = currentButton99;

//Serial.println("100");
  currentButton100 = debounce100(lastButton100);
  if (lastButton100 == LOW && currentButton100 == HIGH)
  {
 

   Serial.println("PB pushed");
    turn_on_shelf_light();
  }


  lastButton100 = currentButton100;


//Serial.println("101");
  currentButton101 = debounce101(lastButton101);


  if (lastButton101 == HIGH && currentButton101 == LOW)
  {
 

    Serial.println("101 pressed feeding mode");
    // mode = 102;

     if (feedmoderunning == 1){
      feedmode = 3; //turn off feeding mode
    }
    else
    {
      feedmode = 1; //turn ON feeding mode
    }
  }
  lastButton101 = currentButton101;



//Serial.println("102");
  currentButton102 = debounce102(lastButton102);
  if (lastButton102 == HIGH && currentButton102 == LOW)
  {

 
    Serial.println("102 pressed w/c mode");
    // mode = 102;

    if (waterchangemoderunning == 1){
      waterchangemoderunning = 0; //turn off waterchange mode
      //LCD.Clear();
    }
    else
    {
      waterchangemode = 1; //turn ON waterchange mode
    }


  }
  lastButton102 = currentButton102;

}
 
 
  
