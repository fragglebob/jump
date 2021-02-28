#include "ofApp.h"
#include "ofSol.h"



void ofSol::create_interop(sol::state& lua, ofApp& app) {

    sol::table of = lua["of"].get_or_create<sol::table>();

    of.set_function("line", sol::overload(
        static_cast<void(*)(float, float, float, float)> (&ofDrawLine),
        static_cast<void(*)(float, float, float, float, float, float)> (&ofDrawLine)
    ));

    of.set_function("box", sol::overload(
        static_cast<void(*)(float)> (&ofDrawBox),
        static_cast<void(*)(float, float, float)> (&ofDrawBox),
        static_cast<void(*)(float, float, float, float)> (&ofDrawBox),
        static_cast<void(*)(float, float, float, float, float, float)> (&ofDrawBox)
    ));

    of.set_function("ball", sol::overload(
        static_cast<void(*)(float)> (&ofDrawSphere),
        static_cast<void(*)(float, float, float, float)> (&ofDrawSphere)
    ));

    of.set_function("pushMatrix", &ofPushMatrix);
    of.set_function("popMatrix", &ofPopMatrix);

    of.set_function("rotate", sol::overload(
        static_cast<void(*)(float)> (&ofRotateDeg),
        static_cast<void(*)(float, float, float, float)> (&ofRotateDeg)
    ));

    of.set_function("rotateX", &ofRotateXDeg);
    of.set_function("rotateY", &ofRotateYDeg);
    of.set_function("rotateZ", &ofRotateZDeg);

    of.set_function("rotateRad", sol::overload(
        static_cast<void(*)(float)> (&ofRotateRad),
        static_cast<void(*)(float, float, float, float)> (&ofRotateRad)
    ));

    of.set_function("rotateXRad", &ofRotateXRad);
    of.set_function("rotateYRad", &ofRotateYRad);
    of.set_function("rotateZRad", &ofRotateZRad);

    of.set_function("scale", sol::overload(
        static_cast<void(*)(float)> (&ofScale),
        static_cast<void(*)(float, float, float)> (&ofScale)
    ));

    of.set_function("translate", sol::overload(
        [](float x, float y) { ofTranslate(x, y, 0.0f); },
        [](float x, float y, float z) { ofTranslate(x, y, z); }
    ));

    of.set_function("pushStyle", &ofPushStyle);
    of.set_function("popStyle", &ofPopStyle);

    of.set_function("line_width", &ofSetLineWidth);

    of.set_function("color", sol::overload(
        [](float r, float g, float b) { ofSetColor((int) r, (int) g, (int) b); },
        [](float r, float g, float b, float a) { ofSetColor((int) r, (int) g, (int) b, (int) a); },
        [](float grey) { ofSetColor(grey); }
    ));


    of.set_function("hsl", [&](float h, float s, float l) { 
        hslColor(h, s, l);
    });

    of.set_function("frame", &ofGetFrameNum);
    of.set_function("time", &ofGetElapsedTimeMillis);

    
    of.set_function("blend_mode", [&](std::string mode) { blendMode(mode); });

    of.set_function("fft", [&app](int pos) -> float { return app.beat.getBand(pos); });

    of.set_function("slider", [&app](int pos) -> float { return app.midiMix.getSlider(pos); });
    of.set_function("knob", [&app](int pos) -> float { return app.midiMix.getKnob(pos); });

    of.set_function("lerp", [](float min, float max, float amt) -> float { return ofLerp(min, max, amt); });

    of.set_function("fx_grid", [&app](float value) {
        app.grid->enablePass(value);
    });

    of.set_function("feedback", [&app](bool enabled) {
        app.feedback->enablePass();
    });

    of.set_function("fx_kale", sol::overload(
        [&app](float value) {
            app.kaleido->enablePass(value);
        },
        [&app](float value, float time) {
            app.kaleido->enablePass(value, time);
        }
    ));

    of.set_function("fx_wave", [&app](float value) {
        app.wave->enablePass(value);
    });

    of.set_function("fx_rgb", [&app](float value) {
        app.rgbshift->enablePass(value);
    });

    of.set_function("fx_bloom", [&app]() {
        app.bloom->enablePass();
    });

    of.set_function("beat", [&app]() {
        return app.beatProgress;
    });

    of.set_function("bar", [&app]() {
        return app.barProgress;
    });

    of.set_function("int_beat", [&app]() {
        return app.currentBeat;
    });

    of.set_function("int_bar", [&app]() {
        return app.currentBar;
    });

}

void ofSol::blendMode(std::string mode) {
    if(mode == "add") {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
    } else if(mode == "alpha") {
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    } else if(mode == "multiply") {
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    } else if(mode == "screen") {
        ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    } else if(mode == "substract") {
        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    } else {
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    }
}

void ofSol::hslColor(float h, float s, float l) {
    float fC = l * s; // Chroma
    float fHPrime = fmod(h / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = l - fC;

    float fR, fG, fB;
    
    if(0 <= fHPrime && fHPrime < 1) {
        fR = fC;
        fG = fX;
        fB = 0;
    } else if(1 <= fHPrime && fHPrime < 2) {
        fR = fX;
        fG = fC;
        fB = 0;
    } else if(2 <= fHPrime && fHPrime < 3) {
        fR = 0;
        fG = fC;
        fB = fX;
    } else if(3 <= fHPrime && fHPrime < 4) {
        fR = 0;
        fG = fX;
        fB = fC;
    } else if(4 <= fHPrime && fHPrime < 5) {
        fR = fX;
        fG = 0;
        fB = fC;
    } else if(5 <= fHPrime && fHPrime < 6) {
        fR = fC;
        fG = 0;
        fB = fX;
    } else {
        fR = 0;
        fG = 0;
        fB = 0;
    }
    
    fR += fM;
    fG += fM;
    fB += fM;


    ofSetColor(fR * 255.f, fG * 255.f, fB * 255.f);
}