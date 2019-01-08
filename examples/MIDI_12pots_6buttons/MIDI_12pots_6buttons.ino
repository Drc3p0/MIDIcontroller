#include "MIDIcontroller.h"

/*This is an example of how to use
  potentiometers, analog sensors piezos as a velocity
  sensitive input, buttons and capacitive sensors.

  The use of a photocell or FSR will be
  demonstrated. I'ts wired like so:
  3.3v--(PHOTO CELL)---\
                        )---Analog Pin
  GND-------/\/\/------/
             10k

  THE PIEZO MUST BE WIRED CORRECTLY FOR THS TO WORK AND TO PREVENT DAMAGE!
  - The black wire of the Piezo, the anode of a diode and
    one side of a 10k resistor should all be connected to ground.
  - The cathode of A SECOND diode should be connected to the voltage.
  - The red wire of the Piezo should be connected to a 470 ohm resistor.
  - The remaining ends of BOTH resistors and BOTH diodes should be connected
    to the same analog pin on the microcontroller.

*/

byte MIDIchannel = 1; //byte is a variable somewhere from 0-255
int prev_val1;
byte velocity = 127;

const int potPin1 = A0;  // Change this to the ANALOG pin you want to use
const int potPin2 = A1;  // Change this to the ANALOG pin you want to use
//const int potPin3 = A2;  // Change this to the ANALOG pin you want to use
const int potPin3 = A3;  // Change this to the ANALOG pin you want to use
const int potPin4 = A4;  // Change this to the ANALOG pin you want to use
const int potPin5 = A5;  // Change this to the ANALOG pin you want to use
const int potPin6 = A6;  // Change this to the ANALOG pin you want to use
//const int potPin7 = A7;  // Change this to the ANALOG pin you want to use
//const int potPin8 = A8;  // Change this to the ANALOG pin you want to use
//const int potPin9 = A9;  // Change this to the ANALOG pin you want to use
//const int potPin10 = A10;  // Change this to the ANALOG pin you want to use
//const int potPin11 = A11;  // Change this to the ANALOG pin you want to use
//const int potPin12 = A12;  // Change this to the ANALOG pin you want to use


//const int touchPin1 = A7; //any Capacitive Touch capable pin
//const int touchPin2 = A8; //any Capacitive Touch capable pinlk
//const int touchPin3 = A9; //any Capacitive Touch capable pin
//const int touchPin4 = A10; //any Capacitive Touch capable pin
//const int touchPin5 = A11; //any Capacitive Touch capable pin
//const int touchPin6 = A12; //any Capacitive Touch capable pin
const int buttonPin1 = 1; int MIDInote1 = 65; int buttonState1 = 0; int lastbuttonState1 = 0;
const int buttonPin2 = 2; int MIDInote2 = 67; int buttonState2 = 0; int lastbuttonState2 = 0;
const int buttonPin3 = 3; int MIDInote3 = 69; int buttonState3 = 0; int lastbuttonState3 = 0;
const int buttonPin4 = 4; int MIDInote4 = 71; int buttonState4 = 0; int lastbuttonState4 = 0;
const int buttonPin5 = 5; int MIDInote5 = 73; int buttonState5 = 0; int lastbuttonState5 = 0;
const int buttonPin6 = 6; int MIDInote6 = 75; int buttonState6 = 0; int lastbuttonState6 = 0;


const int ledPin = 13;   //Set an LED pin for indicating something.

// Pot parameters are: pin, CC number, KILL switch enabled
// When KILL is enabled, separate CC messages (with a different number) will be sent
// when you turn the pot all the way down and when you start turning it up again.
// Simply omit the "KILL" argument if you don't want that.
MIDIpot myPot1(potPin1, 23); 
MIDIpot myPot2(potPin2, 24); 
MIDIpot myPot3(potPin3, 25); 
MIDIpot myPot4(potPin4, 26); 
MIDIpot myPot5(potPin5, 27); 
MIDIpot myPot6(potPin6, 28); 
//MIDIpot myPot7(potPin7, 29); 
//MIDIpot myPot8(potPin8, 30); 
//MIDIpot myPot9(potPin9, 31); 
//MIDIpot myPot10(potPin10, 32); 
//MIDIpot myPot11(potPin11, 33); 
//MIDIpot myPot12(potPin12, 34); 

// MOMENTARY buttons are the default. LATCH or TRIGGER may also be set
//MIDIdrum triggerButton1(touchPin1, 60); // drum parameters are: pin, note number
//MIDIdrum triggerButton2(touchPin2, 62); // drum parameters are: pin, note number
//MIDIdrum triggerButton3(touchPin3, 64); // drum parameters are: pin, note number
//MIDIdrum triggerButton4(touchPin4, 65); // drum parameters are: pin, note number
//MIDIdrum triggerButton5(touchPin5, 67); // drum parameters are: pin, note number
//MIDIdrum triggerButton6(touchPin6, 69); // drum parameters are: pin, note number


void setup() {
  
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);

  // initialize the button pins as a input:
  pinMode(buttonPin1, INPUT_PULLUP); //uses teensy internal pullup on button
  pinMode(buttonPin2, INPUT_PULLUP); //uses teensy internal pullup on button
  pinMode(buttonPin3, INPUT_PULLUP); //uses teensy internal pullup on button
  pinMode(buttonPin4, INPUT_PULLUP); //uses teensy internal pullup on button
  pinMode(buttonPin5, INPUT_PULLUP); //uses teensy internal pullup on button
  pinMode(buttonPin6, INPUT_PULLUP); //uses teensy internal pullup on button
 
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  
  // read the pushbutton input pin:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);

  myPot1.send(); 
  myPot2.send();
  myPot3.send();
  myPot4.send();
  myPot5.send();
  myPot6.send();
//  myPot7.send(); 
//  myPot8.send();
//  //myPot9.send();
//  myPot10.send();
//  myPot11.send();
//  myPot12.send();  


//  triggerButton1.send();
//  triggerButton2.send();
//  triggerButton3.send();
//  triggerButton4.send();
//  triggerButton5.send();
//  triggerButton6.send();



///trigger MIDI from buttonState1
  // compare the buttonState to its previous state
  if (buttonState1 != lastbuttonState1) {
    // if the state has changed, increment the counter
    if (buttonState1 == LOW) {
      // if the current state is HIGH then the button
      // wend from off to on:
      usbMIDI.sendNoteOn(MIDInote1, velocity, MIDIchannel);
      Serial.println("ON");
    }  else {
      // if the current state is LOW then the button
      // wend from on to off:
      usbMIDI.sendNoteOff(MIDInote1, velocity, MIDIchannel);
      Serial.println("OFF");    }
    //delay(10);   
    }
  // save the current state as the last state,
  //for next time through the loop
  lastbuttonState1 = buttonState1;


////////////////////trigger MIDI from buttonState2
  // compare the buttonState to its previous state
  if (buttonState2 != lastbuttonState2) {
    // if the state has changed, increment the counter
    if (buttonState2 == LOW) {
      // if the current state is HIGH then the button
      // wend from off to on:
      usbMIDI.sendNoteOn(MIDInote2, velocity, MIDIchannel);
      Serial.println("ON");
    }  else {
      // if the current state is LOW then the button
      // wend from on to off:
      usbMIDI.sendNoteOff(MIDInote2, velocity, MIDIchannel);
      Serial.println("OFF");    }
    //delay(10);   
    }
  // save the current state as the last state,
  //for next time through the loop
  lastbuttonState2 = buttonState2;


///////////////////////trigger MIDI from buttonState3
  // compare the buttonState to its previous state
  if (buttonState3 != lastbuttonState3) {
    // if the state has changed, increment the counter
    if (buttonState3 == LOW) {
      // if the current state is HIGH then the button
      // wend from off to on:
      usbMIDI.sendNoteOn(MIDInote3, velocity, MIDIchannel);
      Serial.println("ON");
    }  else {
      // if the current state is LOW then the button
      // wend from on to off:
      usbMIDI.sendNoteOff(MIDInote3, velocity, MIDIchannel);
      Serial.println("OFF");    }
    //delay(10);   
    }
  // save the current state as the last state,
  //for next time through the loop
  lastbuttonState3 = buttonState3;


//////////////////////trigger MIDI from buttonState4
  // compare the buttonState to its previous state
  if (buttonState4 != lastbuttonState4) {
    // if the state has changed, increment the counter
    if (buttonState4 == LOW) {
      // if the current state is HIGH then the button
      // wend from off to on:
      usbMIDI.sendNoteOn(MIDInote4, velocity, MIDIchannel);
      Serial.println("ON");
    }  else {
      // if the current state is LOW then the button
      // wend from on to off:
      usbMIDI.sendNoteOff(MIDInote4, velocity, MIDIchannel);
      Serial.println("OFF");    }
    //delay(10);   
    }
  // save the current state as the last state,
  //for next time through the loop
  lastbuttonState4 = buttonState4;


////////////////////////trigger MIDI from buttonState5
  // compare the buttonState to its previous state
  if (buttonState5 != lastbuttonState5) {
    // if the state has changed, increment the counter
    if (buttonState5 == LOW) {
      // if the current state is HIGH then the button
      // wend from off to on:
      usbMIDI.sendNoteOn(MIDInote5, velocity, MIDIchannel);
      Serial.println("ON");
    }  else {
      // if the current state is LOW then the button
      // wend from on to off:
      usbMIDI.sendNoteOff(MIDInote5, velocity, MIDIchannel);
      Serial.println("OFF");    }
    //delay(10);   
    }
  // save the current state as the last state,
  //for next time through the loop
  lastbuttonState5 = buttonState5;


//////////////////////trigger MIDI from buttonState6
  // compare the buttonState to its previous state
  if (buttonState6 != lastbuttonState6) {
    // if the state has changed, increment the counter
    if (buttonState6 == LOW) {
      // if the current state is HIGH then the button
      // wend from off to on:
      usbMIDI.sendNoteOn(MIDInote6, velocity, MIDIchannel);
      Serial.println("ON");
    }  else {
      // if the current state is LOW then the button
      // wend from on to off:
      usbMIDI.sendNoteOff(MIDInote6, velocity, MIDIchannel);
      Serial.println("OFF");    }
    //delay(10);   
    }
  // save the current state as the last state,
  //for next time through the loop
  lastbuttonState6 = buttonState6;
  
}

/* MIDI# - NOTE - SOUND
     35    B  0   Acoustic Bass Drum
     36    C  1   Bass Drum 1
     37    C# 1   Side Stick
     38    D  1   Acoustic Snare
     39    D# 1   Hand Clap
     40    E  1   Electric Snare
     41    F  1   Low Floor Tom
     42    F# 1   Closed Hi Hat
     43    G  1   High Floor Tom
     44    G# 1   Pedal Hi-Hat
     45    A  1   Low Tom
     46    A# 1   Open Hi-Hat
     47    B  1   Low-Mid Tom
     48    C  2   Hi-Mid Tom
     49    C# 2   Crash Cymbal 1
     50    D  2   High Tom
     51    D# 2   Ride Cymbal 1
     52    E  2   Chinese Cymbal
     53    F  2   Ride Bell
     54    F# 2   Tambourine
     55    G  2   Splash Cymbal
     56    G# 2   Cowbell
     57    A  2   Crash Cymbal 2
     58    A# 2   Vibraslap
     59    B  2   Ride Cymbal 2
     60    C  3   Hi Bongo
     61    C# 3   Low Bongo
     62    D  3   Mute Hi Conga
     63    D# 3   Open Hi Conga
     64    E  3   Low Conga
     65    F  3   High Timbale
     66    F# 3   Low Timbale
     67    G  3   High Agogo
     68    G# 3   Low Agogo
     69    A  3   Cabasa
     70    A# 3   Maracas
     71    B  3   Short Whistle
     72    C  4   Long Whistle
     73    C# 4   Short Guiro
     74    D  4   Long Guiro
     75    D# 4   Claves
     76    E  4   Hi Wood Block
     77    F  4   Low Wood Block
     78    F# 4   Mute Cuica
     79    G  4   Open Cuica
     80    G# 4   Mute Triangle
     81    A  4   Open Triangle

  CC number and Description  (MSB = Most Significant Byte https://www.sweetwater.com/insync/msb-lsb-applications/)
  0 Bank Select (MSB)(followed by cc32 & Program Change)
  1 Modulation Wheel
  2 Breath controller
  4 Foot Pedal (MSB)
  5 Portamento Time (MSB) Only use this for portamento time use cc65 to turn on/off
  6 Data Entry (MSB) if you follow cc100=0 & cc101=0 this is pitch bend range
  7 Volume (MSB) Note: CC7 and 11 both adjust the volume. Use cc7 as you would the control on the amplifier - set it and leave it at the beginning of the MIDI track
  8 Balance (MSB) Some synths use it
  10 Pan position (MSB)
  11 Expression (MSB)  Note: CC7 and 11 both adjust the volume. Use cc11 for volume changes during the track (crescendo, diminuendo, swells, etc.)
  12 Effect Control 1 (MSB)
  13 Effect Control 2 (MSB)
  14 Undefined
  15 Undefined
  16 Ribbon Controller or General Purpose Slider 1
  17 Knob 1 or General Purpose Slider 2
  18 General Purpose Slider 3
  19 Knob 2 General Purpose Slider 4
  20 Knob 3 or Undefined
  21 Knob 4 or Undefined
  22-31 are undefined, available for use by synths that let you assign controllers.
  32 Bank Select (LSB) (see cc0)
  33 Modulation Wheel (LSB)
  34 Breath controller (LSB)
  36 Foot Pedal (LSB)
  37 Portamento Time (LSB)
  38 Data Entry (LSB)
  39 Volume (LSB)
  40 Balance (LSB)
  42 Pan position (LSB)
  43 Expression (LSB)
  44 Effect Control 1 (LSB) Roland Portamento on and rate
  45 Effect Control 2 (LSB)
  46-63 may be in use as the LSB for controllers 14-31 in some devices, but I have not seen one yet.
  64 Hold Pedal (on/off)
  Nearly every synth will react to 64 (sustain pedal)
  65 Portamento (on/off)
  66 Sustenuto Pedal (on/off)
  67 Soft Pedal (on/off)
  68 Legato Pedal (on/off)
  69 Hold 2 Pedal (on/off)
  70 Sound Variation
  71 Resonance (aka Timbre)
  72 Sound Release Time
  73 Sound Attack Time
  74 Frequency Cutoff (aka Brightness )
  75 Sound Control 6
  76 Sound Control 7
  77 Sound Control 8
  78 Sound Control 9
  79 Sound Control 10
  80 Decay or General Purpose Button 1 (on/off) Roland Tone level 1
  81 Hi Pass Filter Frequency or General Purpose Button 2 (on/off) Roland Tone level 2
  82 General Purpose Button 3 (on/off) Roland Tone level 3
  83 General Purpose Button 4 (on/off) Roland Tone level 4
  91 Reverb Level
  92 Tremolo Level
  93 Chorus Level
  94 Celeste Level or Detune
  95 Phaser Level
   It's probably best not to use the group below for assigning controllers.
  96 Data Button increment
  97 Data Button decrement
  98 Non-registered Parameter (LSB)
  99 Non-registered Parameter (MSB)
  100 Registered Parameter (LSB)
  101 Registered Parameter (MSB)
   It's very important that you do not use these no matter what unless you want to invoke these functions
  120 All Sound Off
  121 All Controllers Off
  122 Local Keyboard (on/off) You might actually crash your keyboard if you use this one.
  123 All Notes Off
   You typically don't want your synths to change modes on you in the middle of making a song, so don't use these.)
  124 Omni Mode Off
  125 Omni Mode On
  126 Mono Operation
  127 Poly Operation
*/
