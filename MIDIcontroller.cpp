#include "MIDIcontroller.h"


MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);

void MIDI_Send(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable, uint8_t interface) {
  switch (interface)
  {
  case 0 :
	// usb MIDIx16
  	if (type != midi::SystemExclusive) {
		usbMIDI.send(type, data1, data2, channel, cable);
        Serial.println("TRUE");
	} else {
	 unsigned int SysExLength = data1 + data2 * 256;
		usbMIDI.sendSysEx(SysExLength, sysexarray, true, cable);
	}
  case 1 :
	// serial MIDI
  	if (type != midi::SystemExclusive) {
	    // Normal messages, first we must convert usbMIDI's type (an ordinary
        // byte) to the MIDI library's special MidiType.
        midi::MidiType mtype = (midi::MidiType)type;
		MIDI1.send(mtype, data1, data2, channel);
	} else {
	 unsigned int SysExLength = data1 + data2 * 256;
		MIDI1.sendSysEx(SysExLength, sysexarray, true);
	}
	  break;
  case 2 :
      // USBhost MIDI
  	if (type != midi::SystemExclusive) {
		//hostMIDI.send(type, data1, data2, channel, cable);
	} else {
	 unsigned int SysExLength = data1 + data2 * 256;
		//hostMIDI.sendSysEx(SysExLength, sysexarray, true, cable);
	}
      break;
  default :
	  break;
  
  }
}
