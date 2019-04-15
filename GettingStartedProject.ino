
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
PulseSensorPlayground pulseSensor;


int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13;   //  The on-board Arduion LED

const int Output_Type = PROCESSING_VISUALIZER;

int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.


// The SetUp Function:
void setup() {
  pinMode(LED13,OUTPUT);         // pin that will blink to your heartbeat!
   Serial.begin(115200);         // Set's up Serial Communication at certain speed.
  
  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(Output_Type);
  pulseSensor.setThreshold(Threshold);
  
}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.


   if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED13,HIGH);
   } else {
     digitalWrite(LED13,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }


delay(100);
 pulseSensor.outputSample();


  if (pulseSensor.sawStartOfBeat()) {
   pulseSensor.outputBeat();
  }
}
