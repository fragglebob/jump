#include "MidiMix.h"
#include <iostream>

std::vector<std::string> findPortByName(string name, ofxMidiIn midiIn) {
    std::vector<std::string> portList = midiIn.getInPortList();
    std::vector<std::string> hits;

    for(size_t i = 0; i < portList.size(); i++) {
        if(portList[i].find(name) != string::npos) {
            hits.push_back(portList[i]);
        }
    }

    return hits;
}

std::vector<std::string> findPortByName(string name, ofxMidiOut midiOut) {
    std::vector<std::string> portList = midiOut.getOutPortList();
    std::vector<std::string> hits;

    for(size_t i = 0; i < portList.size(); i++) {
        if(portList[i].find(name) != string::npos) {
            hits.push_back(portList[i]);
        }
    }

    return hits;
}

void MidiMix::setup() {
    midiIn.listInPorts();
    std::vector<std::string> inPortList = findPortByName("MIDI Mix", midiIn);
    std::vector<std::string> outPortList = findPortByName("MIDI Mix", midiOut);

    if(!inPortList.empty()) {
        midiIn.openPort(inPortList[0]);
        cout << "Conneting in to " << inPortList[0] << endl;
    } else {
        cout << "Can't find MIDI Mix" << endl;
    }

    if(!outPortList.empty()) {
        midiOut.openPort(outPortList[0]);
        updateLights();
        cout << "Conneting out to " << outPortList[0] << endl;
    } else {
        cout << "Can't find MIDI Mix" << endl;
    }
    
    midiIn.addListener(this);
}

// 1 4 7 10 13 16 19 22
// 2 5 8 11 14 17 20 23
// 3 6 9 12 15 18 21 24
// left 25
// right 26
// solo 27

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
    } else if(eventArgs.status == MIDI_NOTE_ON) {

        if(eventArgs.pitch % 3 == 0) {
            float t = ofGetElapsedTimef();
            ofNotifyEvent(onBpmTap, t, this);
        }
    
        // if(eventArgs.pitch < 27) {
        //     lights[eventArgs.pitch-1] = !lights[eventArgs.pitch-1];
        //     midiOut.sendNoteOn(1, eventArgs.pitch, lights[eventArgs.pitch-1] ? 0x7f : 0x00);
        // }

        // cout << "note: " << eventArgs.pitch << endl;
    }

    
}


void MidiMix::updateLights() {

    if(!midiOut.isOpen()) {
        return;
    }

    for (size_t i = 0; i < sizeof(lights); i++)
    {
        midiOut.sendNoteOn(1, i + 1, lights[i] ? 0x7f : 0x00);
    }
    

}