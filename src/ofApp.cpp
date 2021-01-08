#include "ofApp.h"
#include <memory>
#include <random>

void line(float x1, float y1, float x2, float y2) {
    ofDrawLine(x1, y1, x2, y2);
}

//--------------------------------------------------------------
void ofApp::setup(){

    settings.loadFile("settings.xml");

    aubiobeat.setup();
    ofAddListener(aubiobeat.gotBeat, this, &ofApp::beatEvent);

    ofSetFrameRate(60);

    soundStream.printDeviceList();

    ofEnableAntiAliasing();
    ofEnableDepthTest();
    ofEnableAlphaBlending();

    ofSoundStreamSettings streamSettings;
    streamSettings.numInputChannels = 1;
    streamSettings.numOutputChannels = 2;
    streamSettings.bufferSize = beat.getBufferSize();
    streamSettings.setInListener(this);

    string audioInDeviceName = settings.getValue("settings:audioIn", "default");

    if(audioInDeviceName != "default") {
        auto devices = soundStream.getMatchingDevices(audioInDeviceName);
        if(!devices.empty()){
            streamSettings.setInDevice(devices[0]);
        }
    }
    
    soundStream.setup(streamSettings);

    ofSetupScreenPerspective(1200,1200,0,0,0);
    ofSetGlobalAmbientColor(ofColor(0, 0, 0));
    ofEnableLighting();
    ofSetSmoothLighting(true);

    ofSetBackgroundAuto(false);

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

    feedback = post.createPass<FeedbackPass>();

    // bloom = post.createPass<BloomPass>();
    kaleido = post.createPass<MyKidoPass>();
    grid = post.createPass<GridShiftPass>();
    wave = post.createPass<SliceWavePass>();


    
    
    midiMix.setup();
    
    setBpm(120);

    for (size_t i = 0; i < 10; i++)
    {
        modTimes[i] = 0;
        errors[i] = 0;
    }

    cout << "setting up lua" << endl;
    lua.open_libraries(sol::lib::base, sol::lib::math);
    cout << "set_function" << endl;

    solHelper.create_interop(lua, *this);

    cout << "script_file" << endl;
    loadScript(ofToDataPath("0.lua"));
    cout << "setup lua complete" << endl;

    modTimes[0] = std::filesystem::last_write_time(ofToDataPath("0.lua"));

    setupFeedbackLoop();

}

void ofApp::setupFeedbackLoop()
{
    ofFbo::Settings s;
    
    s.width = ofGetWidth();
    s.height =ofGetHeight();
    s.textureTarget = GL_TEXTURE_2D;

    currentFrame.allocate(s);
    feedbackFrame.allocate(s);

    currentFrame.begin();
    ofClear(255,255,255, 0);
    currentFrame.end();

    feedbackFrame.begin();
    ofClear(255,255,255, 0);
    feedbackFrame.end();
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

    float beatsElapsedSinceSet = diff / secondsPerBeat + beatsCounted;

    int totalBeats = (int) beatsElapsedSinceSet;
    
    currentBar = totalBeats / 4;
    currentBeat = totalBeats % 4;

    beatProgress = beatsElapsedSinceSet;
    barProgress = beatsElapsedSinceSet / 4.f;


    // TODO: keeps crashing when sending light
    // // 0 1 2 3  4  5  6  7
    // // 3 6 9 12 15 18 21 24

    // for (size_t i = 0; i < 8; i++)
    // {
    //     midiMix.lights[(i + 1) * 3 - 1] = false;
    // }

    // int light = currentBeat;

    // if(currentBar % 2 != 0) {
    //     light += 4;
    // }

    // midiMix.lights[(light + 1) * 3 - 1] = true;

    // midiMix.updateLights();

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

    if(ofGetFrameNum() % 10 == 0) {
        std::time_t mTime = std::filesystem::last_write_time(ofToDataPath("0.lua"));

        if(mTime > modTimes[0]) {
            modTimes[0] = mTime;
            errors[0] = false;
            loadScript(ofToDataPath("0.lua"));
        }
    }

    updateBeat();

}


//--------------------------------------------------------------
void ofApp::draw(){

    // disable fx for code to enabled later
    kaleido->disable();
    grid->disable();
    wave->disable();
    feedback->disable();
    // bloom->disable();

    // ofBackground(0,0,0,255);
    ofBackground(0,0,0,255);
    ofClear(0,0,0,0);
    // 

    ofEnableAlphaBlending();

    post.begin();

    

    // beginFeedback();



   

    // if(feedbackEnabled) {
    //     ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //     ofSetDepthTest(false);
    //     drawFeedback(feedbackFrame, ofGetWidth(), ofGetHeight());
    //     ofSetDepthTest(true);
    //     feedbackEnabled = false;
    //     ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    // }

    

    ofDisableLighting();

    auto midX = float(ofGetWidth() / 2.0);
    auto midY = float(ofGetHeight() / 2.0);

    ofPushStyle();
    ofPushMatrix();

    ofTranslate(midX,midY);

    ofEnableLighting();

    light.enable();
    amb.enable();

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


    ofPopStyle();
    ofPopMatrix();

    // endFeedback();

    post.end();

    

    

}

void ofApp::beginFeedback() {

    currentFrame.begin(OF_FBOMODE_NODEFAULTS);

    // // ofMatrixMode(OF_MATRIX_PROJECTION);
    // ofPushMatrix();
    
    // // ofMatrixMode(OF_MATRIX_MODELVIEW);
    // ofPushMatrix();
    
    // ofViewport(0, 0, currentFrame.getWidth(), currentFrame.getHeight());
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    // ofPushStyle();
    // glPushAttrib(GL_ENABLE_BIT);

}


void ofApp::endFeedback() {

    
    // glPopAttrib();
    // ofPopStyle();
    
    // // ofMatrixMode(OF_MATRIX_PROJECTION);
    // ofPopMatrix();
    
    // // ofMatrixMode(OF_MATRIX_MODELVIEW);
    // ofPopMatrix();
    
    currentFrame.end();

    feedbackFrame.begin(OF_FBOMODE_NODEFAULTS);
    drawFeedback(currentFrame, ofGetWidth(), ofGetHeight());
    feedbackFrame.end();

    // ofViewport(0, 0, ofGetWidth(), ofGetHeight());
    
    drawFeedback(currentFrame, ofGetWidth(), ofGetHeight());

}

void ofApp::drawFeedback(ofFbo& fbo, int width, int height) {

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    ofSetColor(255, 255, 255);
    fbo.draw(0,0, width, height);
    glPopAttrib();
    ofPopStyle();
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
    feedback->allocateFbo();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioIn(ofSoundBuffer & input) {
    beat.audioReceived(input);
    aubiobeat.audioIn(input);
}

void ofApp::beatEvent(float & time) {
    setBpm(aubiobeat.bpm);
    beatsCounted++;
}
