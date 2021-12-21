#include "ofApp.h"
#include <memory>
#include <random>

void line(float x1, float y1, float x2, float y2) {
    ofDrawLine(x1, y1, x2, y2);
}

//--------------------------------------------------------------
void ofApp::setup(){

    ofDisableArbTex();

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
    string audioInDeviceNameApi = settings.getValue("settings:audioInApi", "default");

    ofSoundDevice::Api api = ofSoundDevice::Api::DEFAULT;

    if(audioInDeviceNameApi == "default") {
        api = ofSoundDevice::Api::DEFAULT;
    } else if(audioInDeviceNameApi == "alsa") {
        api = ofSoundDevice::Api::ALSA;
    } else if(audioInDeviceNameApi == "pulse") {
        api = ofSoundDevice::Api::PULSE;
    } else if(audioInDeviceNameApi == "oss") {
        api = ofSoundDevice::Api::OSS;
    } else if(audioInDeviceNameApi == "jack") {
        api = ofSoundDevice::Api::JACK;
    } else if(audioInDeviceNameApi == "osx_core") {
        api = ofSoundDevice::Api::OSX_CORE;
    } else if(audioInDeviceNameApi == "ms_wasapi") {
        api = ofSoundDevice::Api::MS_WASAPI;
    } else if(audioInDeviceNameApi == "ms_asio") {
        api = ofSoundDevice::Api::MS_ASIO;
    } else if(audioInDeviceNameApi == "ms_ds") {
        api = ofSoundDevice::Api::MS_DS;
    }

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

    rgbshift = post.createPass<RGBShiftPass>();
    bloom = post.createPass<BloomPass>();
    kaleido = post.createPass<MyKidoPass>();
    grid = post.createPass<GridShiftPass>();
    wave = post.createPass<SliceWavePass>();
    feedback = post.createPass<FeedbackPass>();
    ascii = post.createPass<AsciiPass>();
    matrix = post.createPass<MatrixPass>();
    
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

    currentFbo = 0;
    setupRenderingFbos();
    

}

void ofApp::setupRenderingFbos()
{
    ofFbo::Settings s;
    
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.textureTarget = GL_TEXTURE_2D;

    s.useDepth = true;
    s.depthStencilInternalFormat = GL_DEPTH_COMPONENT24;
    s.depthStencilAsTexture = true;

    for (size_t i = 0; i < 2; i++)
    {
        renderingFlop[i].allocate(s);
        renderingFlop[i].begin();
        ofClear(255,255,255, 0);
        renderingFlop[i].end();
    }
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

void ofApp::doRenderPass(std::function<void(ofFbo&, ofFbo&)> func) {

    renderingFlop[currentFbo].end();

    int nextFbo = currentFbo == 1 ? 0 : 1;

    renderingFlop[nextFbo].begin(OF_FBOMODE_NODEFAULTS);
    ofClear(0,0,0,0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    renderingFlop[nextFbo].end();


    ofPushStyle();
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    ofSetColor(255, 255, 255);
    ofEnableAlphaBlending();

    ofDisableDepthTest();
    func(renderingFlop[currentFbo], renderingFlop[nextFbo]);
    ofEnableDepthTest();

    glPopAttrib();
    ofPopStyle();

    glEnable(GL_LIGHTING);

    currentFbo = nextFbo;

    renderingFlop[currentFbo].begin(OF_FBOMODE_NODEFAULTS);

}

//--------------------------------------------------------------
void ofApp::draw(){

    currentFbo = 0;

    for (size_t i = 0; i < 2; i++)
    {
        renderingFlop[i].begin();
        ofClear(0,0,0,0);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        renderingFlop[i].end();
    }

    // disable fx for code to enabled later
    // kaleido->disable();
    // grid->disable();
    // wave->disable();
    // feedback->disable();
    // bloom->disable();

    // ofBackground(0,0,0,255);
    ofBackground(0,0,0,255);
    ofClear(0,0,0,0);
    // 

    ofEnableAlphaBlending();

    // post.begin();

    ofDisableLighting();

    auto midX = float(ofGetWidth() / 2.0);
    auto midY = float(ofGetHeight() / 2.0);

    ofPushStyle();
    glPushAttrib(GL_ENABLE_BIT);
    ofPushMatrix();

    ofTranslate(midX,midY);

    ofEnableLighting();

    light.enable();
    amb.enable();

    renderingFlop[currentFbo].begin(OF_FBOMODE_NODEFAULTS);

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

    renderingFlop[currentFbo].end();

    

    ofPopStyle();
    ofPopMatrix();


    renderingFlop[currentFbo].draw(0, 0, ofGetWidth(), ofGetHeight());

    // post.end();

    post.clearEnabled();

    

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
    setupRenderingFbos();
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

void ofApp::startTexture(std::string filepath) {

    auto search = textures.find(filepath);

    if (search == textures.end()) {

        auto loadSearch = loadedTextures.find(filepath);

        if(loadSearch != loadedTextures.end()) {
            return;
        }

        std::shared_ptr<ofTexture> tex = make_shared<ofTexture>();

        bool loaded = ofLoadImage(*tex, filepath);

        loadedTextures.insert(std::pair{filepath, loaded});

        if(loaded == true) {
            textures.insert(std::pair{filepath, tex});
            tex->bind();
        } else {
            std::cout << "couldn't load image: " << filepath << std::endl;
        }
        return;
    }

    search->second->bind();
}

void ofApp::endTexture(std::string filepath) {
    auto search = textures.find(filepath);

    if (search != textures.end()) {
        search->second->unbind();
    }
}