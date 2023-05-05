
/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Use This Sketch To------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks the builtin LED with user's Heartbeat.
--------------------------------------------------------------------*/

#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int fan_control_pin=3;    //VAR for fan 1 PIN
const int fan_control_pin2 = 5; //VAR for fan 2 PIN
const int led = 12; //VAR for LED
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   

  Serial.begin(9600);          

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("PulseSensor Object Created!");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }

  //setting up the fan
  pinMode(fan_control_pin, OUTPUT);
  digitalWrite(fan_control_pin, LOW);

  pinMode(fan_control_pin2, OUTPUT);
  digitalWrite(fan_control_pin2, LOW);

  // initialize digital pin LED as an output.
  pinMode(led, OUTPUT);
}



void loop() {
int myBPM = pulseSensor.getBeatsPerMinute();      // Calculates BPM
 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
 if (myBPM > 100){
   Serial.println("Motion Sickness Onset");
   digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
   digitalWrite(fan_control_pin, HIGH);
   digitalWrite(fan_control_pin2, HIGH);
 }
 else {
   Serial.println("No Motion Sickness");
   digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
   digitalWrite(fan_control_pin, LOW);
   digitalWrite(fan_control_pin2, LOW);
 }

}

  delay(20);                    // considered best practice in a simple sketch.

}

  
