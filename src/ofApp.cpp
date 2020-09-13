#include "ofApp.h"
#include <memory>
#include <random>

void line(float x1, float y1, float x2, float y2) {
    ofDrawLine(x1, y1, x2, y2);
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);

    // soundStream.printDeviceList();

    ofEnableAntiAliasing();
    ofEnableDepthTest();

    ofSoundStreamSettings streamSettings;
    streamSettings.numInputChannels = 1;
    streamSettings.bufferSize = beat.getBufferSize();
    streamSettings.setInListener(this);

    auto devices = soundStream.getMatchingDevices("Scarlett 2i4 USB");
    if(!devices.empty()){
        streamSettings.setInDevice(devices[0]);
    }

    soundStream.setup(streamSettings);



    ofSetupScreenPerspective(1200,1200,0,0,0);
    ofSetGlobalAmbientColor(ofColor(0, 0, 0));
    ofEnableLighting();
    ofSetSmoothLighting(true);

    light.setAmbientColor(ofColor(0,0,0));
    light.setDiffuseColor(ofColor(255,255,255));
    light.setSpecularColor(ofColor(255,255,255));
    light.setPointLight();
    light.boom(30);
    light.setAttenuation(1.f,0.f,0.f);
    light.setPosition(0,0,1000);
    amb.setAmbientColor(ofColor(50.0, 50.0, 50.0, 50.0));

    post.init(ofGetWidth(), ofGetHeight());
    // post.createPass<RGBShiftPass>();
    bloom = post.createPass<BloomPass>();
    kaleido = post.createPass<MyKidoPass>();
    grid = post.createPass<GridShiftPass>();
    wave = post.createPass<SliceWavePass>();
    
    ofSetBackgroundAuto(true);

    midiMix.setup();
    ofAddListener(midiMix.onBpmTap, this, &ofApp::handleBpmTap);
    setBpm(120);

    for (size_t i = 0; i < 10; i++)
    {
        modTimes[i] = 0;
        errors[0] = 0;
    }

    cout << "setting up lua" << endl;
    lua.open_libraries(sol::lib::base, sol::lib::math);
    cout << "set_function" << endl;

    solHelper.create_interop(lua, *this);

    cout << "script_file" << endl;
    loadScript(ofToDataPath("0.lua"));
    cout << "setup lua complete" << endl;

    modTimes[0] = std::filesystem::last_write_time(ofToDataPath("0.lua"));
    
}

void ofApp::handleBpmTap(float &time) {

    if(time - lastBpmTap > 4 || lastBpmTap == 0.f) {
        bpmTapCount = 0;
        for (size_t i = 0; i < 10; i++)
        {
            bpmTaps[i] = 0.0f;
        }
        lastBpmTap = time;
        return;
    }

    if(bpmTapCount > 9) {
        for (size_t i = 1; i < 10; i++)
        {
            bpmTaps[i-1] = bpmTaps[i];
        }
        bpmTaps[9] = time - lastBpmTap;
    } else {
        bpmTaps[bpmTapCount] = time - lastBpmTap;
    }

    if(bpmTapCount > 4) {
        size_t itemsToCheck = min(bpmTapCount + 1, 10);
        float total = 0.f;
        for (size_t i = 0; i < itemsToCheck; i++)
        {
            total += bpmTaps[i];
        }

        setBpm(60 / (total / itemsToCheck));
        
    }

    lastBpmTap = time;
    bpmTapCount++;
    
}

void ofApp::setBpm(float bpm) {
    
    currentBpm = bpm;
    currentBpmSetTime = ofGetElapsedTimef();
    updateBeat();
    cout << "bpm: " << bpm << endl;
}

void ofApp::updateBeat() {

    float now = ofGetElapsedTimef();

    float secondsPerBeat = 60.f / currentBpm;

    float diff = now - currentBpmSetTime;

    float beatsElapsedSinceSet = diff / secondsPerBeat;

    int totalBeats = (int) beatsElapsedSinceSet;
    
    currentBar = totalBeats / 4;
    currentBeat = totalBeats % 4;

    beatProgress = beatsElapsedSinceSet;
    barProgress = beatsElapsedSinceSet / 4.f;

    // 0 1 2 3  4  5  6  7
    // 3 6 9 12 15 18 21 24

    for (size_t i = 0; i < 8; i++)
    {
        midiMix.lights[(i + 1) * 3 - 1] = false;
    }

    int light = currentBeat;

    if(currentBar % 2 != 0) {
        light += 4;
    }

    midiMix.lights[(light + 1) * 3 - 1] = true;

    midiMix.updateLights();

}

bool ofApp::loadScript(std::string path) {

    sol::load_result loaded_file = lua.load_file(path);

    if (!loaded_file.valid()) { // This checks the syntax of your script, but does not execute it
        errors[0] = true;
        sol::error err = loaded_file;
        std::string what = err.what();
        std::cout << "call failed, sol::error::what() is " << what << std::endl;
        return false;
    }
    
    sol::protected_function script_func = loaded_file;
    sol::protected_function_result result = script_func();

    if (!result.valid()) {
        errors[0] = true;
        sol::error err = result;
        sol::call_status status = result.status();
        std::cout << "Something went horribly wrong running the code: " << sol::to_string(status) << " error" << "\n\t" << err.what() << std::endl;
        return false;
    }

    return true;
}

//--------------------------------------------------------------
void ofApp::update(){
    beat.update(ofGetElapsedTimeMillis());

    std::time_t mTime = std::filesystem::last_write_time(ofToDataPath("0.lua"));

    if(mTime > modTimes[0]) {
        modTimes[0] = mTime;
        errors[0] = false;
        loadScript(ofToDataPath("0.lua"));
    }

    updateBeat();

}


//--------------------------------------------------------------
void ofApp::draw(){

    // disable fx for code to enabled later
    kaleido->disable();
    grid->disable();
    wave->disable();

    ofBackground(0,0,0,255);
    post.begin();

    ofDisableLighting();

    auto midX = float(ofGetWidth() / 2.0);
    auto midY = float(ofGetHeight() / 2.0);

    // auto maxMidXY = min(midY, midX);

    ofPushStyle();
    ofPushMatrix();

    ofTranslate(midX,midY);

    if(errors[0] == false) {
        sol::protected_function drawFx = lua["draw"];
        auto fxRes = drawFx();
        if ( !fxRes.valid() ) {
            errors[0] = true;
            sol::error err = fxRes;
            std::string what = err.what();
            std::cout << what << std::endl;
        }
    }
    

//     ofEnableBlendMode(OF_BLENDMODE_DISABLED);

//     ofEnableLighting();

//     light.enable();
//     amb.enable();

//     ofSeedRandom(425624562456);
//     std::mt19937 generator (842456224616513);
//     std::uniform_real_distribution<double> uniform01(0.0, 1.0);

//     int layers = 10;

//     float triButtom = 100;
//     float triHeight = 1.73205080757f / 2.f * triButtom;
//     float falhTriHeight = triHeight / 2.f;
//     float falhtriButtom = triButtom / 2.f;

//     ofVec3f center = ofVec3f(0,0,0);

//     for (int l = 0; l < layers; ++l) {
//         ofPushMatrix();

//         ofRotateDeg(ofGetElapsedTimef(), ofRandomf(), ofRandomf(), ofRandomf());

//         float ySize = falhTriHeight * (beat.getBand((layers - l) * 2  + 2) * midiMix.sliders[8]);
//         float xSize = falhtriButtom * (beat.getBand((l) * 2  + 2) * midiMix.sliders[8]);

//         float dFromCenter = 280.0 + float((l) * 40);

//         ofSetColor(ofColor::fromHsb((l / double(layers)) * 255, 250, 200.0));


//         ofRotateDeg(ofGetFrameNum() / 10.f, ofRandomf(), ofRandomf(), ofRandomf());
//         for (int j = 0; j < 100 + (l * l * 10); ++j) {

//             ofPushMatrix();



//             double theta = 2 * M_PI * uniform01(generator);
//             double phi = acos(1 - 2 * uniform01(generator));
//             double x = sin(phi) * cos(theta);
//             double y = sin(phi) * sin(theta);
//             double z = cos(phi);
// //
// //            double x2 = sin(phi) * cos(theta + 0.1);
// //            double y2 = sin(phi) * sin(theta + 0.1);
// //            double z2 = cos(phi);
// //
// //            double x3 = sin(phi + 0.1) * cos(theta + 0.1);
// //            double y3 = sin(phi + 0.1) * sin(theta + 0.1);
// //            double z3 = cos(phi + 0.1);
// //
// //            ofRotateRad(theta, x, y, z);

//             ofTranslate(x * dFromCenter, y * dFromCenter, z * dFromCenter);

//             // ofDrawSphere(xSize);
// //            ofScale(xSize);
// //            ofDrawTriangle(
// //                x * dFromCenter, y * dFromCenter, z * dFromCenter,
// //                x2 * dFromCenter, y2 * dFromCenter, z2 * dFromCenter,
// //                x3 * dFromCenter, y3 * dFromCenter, z3 * dFromCenter
// //            );

// //            ofVec3f pos = ofVec3f(x, y, z);
// //            pos.normalize();
// //
// //            float angle = center.angleRad(pos);


// //            ofRotateRad(angle, pos.x, pos.y, pos.z);
// //


//             ofPopMatrix();


//         }
//         ofPopMatrix();
//     }

//    light.draw();

//    ofSeedRandom();

//    float w = 12,h = 12,d = 12;
//    float step = 100;
//
//    float xMin = (step - (w * step)) / 2.0f;
//    float xMax = ((w * step) - step) / 2.0f;
//    float yMin = (step - (h * step)) / 2.0f;
//    float yMax = ((h * step) - step) / 2.0f;
//    float zMin = (step - (d * step)) / 2.0f;
//    float zMax = ((d * step) - step) / 2.0f;
//    for (float x = xMin; x <= xMax; x += step) {
//        for (float y = yMin; y <= yMax; y += step) {
//            for (float z = zMin; z <= zMax; z += step) {
//                ofPushMatrix();
//                ofTranslate(x, y, z);
//                ofDrawBox(0,0,0, beat.getBand(7) * 50.f);
//                ofPopMatrix();
//            }
//        }
//    }



    ofPopStyle();
    ofPopMatrix();




    post.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    post.resize(w, h, false);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioIn(ofSoundBuffer & input) {

    float t = ofGetElapsedTimef();


    beat.audioReceived(input);
    gist.processAudioFrame(input.getBuffer());

    gist_peak = gist.peakEnergy();
    gist_rms = gist.rootMeanSquare();
    gist_zcr = gist.zeroCrossingRate();

    const std::vector<float>& melSpec = gist.getMelFrequencySpectrum();

    gist_mel_spec = melSpec;

    std::vector<float> magSpec = gist.getMagnitudeSpectrum();

    detektor.process(t, magSpec);

}
