#include "MidiMix.h"
#include <iostream>

std::vector<std::string> findPortByName(string name, ofxMidiIn midiIn) {
    std::vector<std::string> portList = midiIn.getInPortList();
    std::vector<std::string> hits;

    for(size_t i = 0; i < portList.size(); i++) {
        if(portList[i].find("MIDI Mix MIDI") != string::npos) {
            hits.push_back(portList[i]);
        }
    }

    return hits;
}

void MidiMix::setup() {
    midiIn.listInPorts();
    std::vector<std::string> portList = findPortByName("MIDI Mix", midiIn);

    if(!portList.empty()) {
        midiIn.openPort(portList[0]);
        cout << "Conneting to " << portList[0] << endl;
    } else {
        cout << "Can't find MIDI Mix" << endl;
    }

    
    midiIn.addListener(this);
}

void MidiMix::newMidiMessage(ofxMidiMessage& eventArgs) {

    if(eventArgs.status == MIDI_CONTROL_CHANGE) {
        int index;
        
        if(eventArgs.control >= 0x10 && eventArgs.control <= 0x1F) {
            index = eventArgs.control - 0x10;
        } else {
            index = eventArgs.control - 0x2E + 0x10;
        }

        int column = floor(index / 4.0);
        int row = index % 4;

        if(row == 3 || eventArgs.control == 0x3E) {
            int sliderNumber = column;
            sliders[sliderNumber] = eventArgs.value / 127.f;
        } else {
            int knobNumber = (column * 3) + row;
            knobs[knobNumber] = eventArgs.value / 127.f;
        }
    }

    
}