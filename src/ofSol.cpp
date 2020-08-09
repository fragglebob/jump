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

    of.set_function("frame", &ofGetFrameNum);
    of.set_function("time", &ofGetElapsedTimeMillis);

    
    of.set_function("blend_mode", [&](std::string mode) { blendMode(mode); });

    of.set_function("fft", [&app](int pos) -> float { return app.beat.getBand(pos); });

    of.set_function("slider", [&app](int pos) -> float { return app.midiMix.getSlider(pos); });
    of.set_function("knob", [&app](int pos) -> float { return app.midiMix.getKnob(pos); });

    of.set_function("lerp", [](float min, float max, float amt) -> float { return ofLerp(min, max, amt); });

    of.set_function("fx_grid", [&app](float value) {
        app.grid->enable();
        app.grid->setRows(value);
    });

    of.set_function("fx_kale", [&app](float value) {
        app.kaleido->enable();
        app.kaleido->setSegments(value);
    });

    of.set_function("fx_wave", [&app](float value) {
        app.wave->enable();
        app.wave->setSegments(value);
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