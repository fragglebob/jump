#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class MidiMix : public ofxMidiListener  {
    public:

    ofxMidiIn midiIn;
    ofxMidiOut midiOut;

    void setup();
    void newMidiMessage(ofxMidiMessage& eventArgs);

    float knobs[24];
    float sliders[9];
    bool lights[26];

    float getSlider(int pos) {
        if(pos < 0 || pos >= 9) {
            return 0.f;
        }
        return sliders[pos];
    }
    float getKnob(int pos) {
        if(pos < 0 || pos >= 24) {
            return 0.f;
        }
        return knobs[pos];
    }

    void updateLights();

};