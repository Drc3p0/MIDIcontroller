#ifndef MIDIcontroller_h
#define MIDIcontroller_h

#include "MIDIbutton.h"
#include "MIDIpot.h"
//#include "MIDIenc.h"
//#include "MIDIcapSens.h"
//#include "MIDIdrum.h"
#include "MIDI.h"

extern void MIDI_Send(byte type, byte data1, byte data2, byte channel, const uint8_t *sysexarray, byte cable, byte interface);

#endif

