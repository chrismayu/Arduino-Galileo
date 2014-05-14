/**
 * This demo code demonstrate all functionnalities of the PCF8575 library.
 *
 * PCF8575 pins map :
 * 0: led
 * 1: led
 * 2: led
 * 3: button + pull-up resistor
 */

/* Dependencies */
#include <Wire.h>    // Required for I2C communication
#include "PCF8574.h" // Required for PCF8575

#define redchip 0x24 // device addresses for PCF8547Ns on each LED colour bank 
#define yellowchip 0x21 // addresses in this example match the published schematic in the tutorial
#define greenchip 0x20 // you will need to change addresses if you vary from the schematic


/** PCF8575 instance */
PCF8574 expander;

/** setup() */
void setup() {

  /* Setup serial for debug */
  Serial.begin(57600);
  
  /* Start I2C bus and PCF8574 instance */
  expander.begin(0x21);
  
  /* Setup some PCF8575 pins for demo */
  expander.pinMode(0, OUTPUT);
  expander.pinMode(1, OUTPUT);
  expander.pinMode(2, OUTPUT);
  //expander.pinMode(3, INPUT_PULLUP);
  
 
}

 

/** loop() */
void loop() {

  /* Blink demo */
   Serial.print("Blink  demo");
  expander.blink(1, 5, 500); // Blink led 2
  delay(1000);
  expander.blink(2, 5, 500); // Blink led 3
  delay(1000);

  /* DigitalWrite demo */
   Serial.print("DigitalWrite  demo");
  expander.digitalWrite(1, HIGH); // Turn off led 2
  delay(500);
  expander.digitalWrite(2, HIGH); // Turn off led 3
  delay(500);
  expander.digitalWrite(1, LOW);  // Turn on led 2
  delay(500);
  expander.digitalWrite(2, LOW);  // Turn on led 3
  delay(500);

  Serial.print("Toggle demo");
  /* Toggle demo */
  expander.toggle(1);  // Toggle led 2
  expander.toggle(2);  // Toggle led 3
  delay(1000);
  expander.toggle(1);  // Toggle led 2
  expander.toggle(2);  // Toggle led 3
  delay(1000);

  /* Direct pins acces demo (does not with input setup) */
  //expander.write(255); // All led off
  //delay(1000);
  //expander.write(0);   // All led on
  //delay(1000);

 

  /* Final demo (warning: will make button bug) */
  //expander.set();   // All led off
  //delay(1000);
  //expander.clear(); // All led on
  delay(5000);
}
