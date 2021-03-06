#include "MIDIcontroller.h"
#include "MIDI.h"

// IMPORTANT: these are globals - match names exactly!!!
byte MIDIchannel = 5;   // (1 to 16) what channel you want the MIDI commands to be sent to
byte MIDIcable = 0;     // (1 to 16) leave at 0 for now..you'll use Serial + MIDIx4 for values greater than 1 
byte MIDIface = 1; // 0=USB, 1=Serial, 2=HostUSB  Serial is for hardware midi (use serial pin 1) 

const int latchPin = 5; //any digital pin
const int touchPin = 7; //any Capacitive Touch capable pin
const int ledPin = 13;   //Set an LED to show the state of a latch button.


// MOMENTARY buttons are the default. LATCH or TRIGGER may also be set
MIDIbutton latchButton(latchPin, 21, TRIGGER);           // Control Change #21
MIDIbutton triggerButton(touchPin, 15, TRIGGER); // CC #15, capacitive touch threshold 5000

void setup(){
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  latchButton.send();
  triggerButton.send();
  digitalWrite(ledPin, latchButton.state);
}
