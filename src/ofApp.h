#ifndef _OFAPP_H_
#define _OFAPP_H_

#pragma once


#include "ofMain.h"
#include "ofxBeat.h"
#include "MidiMix.h"
#include "myPostProcessing.h"
#include "GridShiftPass.h"
#include "SliceWavePass.h"
#include "MyKidoPass.h"
#include "FeedbackPass.h"
#include "BloomPass.h"
#include "RGBShiftPass.h"
#include "AsciiPass.h"
#include "MatrixPass.h"
#include "ofSol.h"
#include "ofxAubioBeat.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp {

	public:

		sol::state lua;
		ofSol solHelper;

        ofLight light;
        ofLight amb;
        myPostProcessing post;

        ofxBeat beat;
        ofSoundStream soundStream;

		MidiMix midiMix;

		std::time_t modTimes[10];
		bool errors[10];

		MyKidoPass::Ptr kaleido;
		BloomPass::Ptr bloom;
		RGBShiftPass::Ptr rgbshift;
		GridShiftPass::Ptr grid;
		SliceWavePass::Ptr wave;
		FeedbackPass::Ptr feedback;
		AsciiPass::Ptr ascii;
		MatrixPass::Ptr matrix;

		ofxAubioBeat aubiobeat;
		float lastBeatTime = 0.f;
		float lastBpm = 120.0f;

		int currentFbo = 0;
		ofFbo renderingFlop[2];

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void audioIn(ofSoundBuffer & input);

		void doRenderPass(std::function<void(ofFbo&, ofFbo&)> func);

		int bpm = 120;
		int bpmTapCount = 0;
		float lastBpmTap;
		float bpmTaps[10];

		void handleBpmTap(float &time);

		uint64_t beatsCounted;

		float currentBpm;
		float currentBpmSetTime;

		int currentBeat;
		int currentBar;

		float barProgress;
		float beatProgress;

		void setBpm(float bpm);

		void updateBeat();
		void beatEvent(float & time);

		bool feedbackEnabled = false;

		void setFeeback(bool feedback) { feedbackEnabled = feedback; }

		ofxXmlSettings settings;
		
	private:

		void setupRenderingFbos();

		bool loadScript(std::string path);

		void beginFeedback();
		void endFeedback();
		void drawFeedback(ofFbo& fbo, int width, int height);
};

#endif