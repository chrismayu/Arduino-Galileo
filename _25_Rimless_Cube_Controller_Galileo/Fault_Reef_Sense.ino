



 

void Send_message_to_Reef_Sense(String Fault_Zone,String Fault_Alert ) {





   Serial.println("Going to TRY to send FAULT data");



  bottom_relays.digitalWrite(Grounding_plug, HIGH); /// turn off grounding probe

 delay(500);

    

  





 String faultdata = "{\"f_z\":\"" + Fault_Zone + "\", \"t_n\":\"" + arduino_reef_tank_id + "\", \"f_a\":\"" + Fault_Alert + "\"}";

 

// Serial.print("Fault Data to Send: ");

// Serial.println(faultdata);

 





  

  String uri = ("/faults");

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

  client.println(faultdata.length());

  client.println();

   Serial.print("data:-----");

 Serial.println(faultdata);

  client.print(faultdata);

  client.println();

  Serial.println("done sending fault data");

    

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



digitalWrite(Grounding_plug, LOW); /// turn off grounding probe





}







 

 






