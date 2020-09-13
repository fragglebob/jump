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
#include "ofSol.h"

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
		GridShiftPass::Ptr grid;
		SliceWavePass::Ptr wave;

		std::deque<float> subBandBeatTimes[FFT_SUBBANDS];
		bool hasBeatBeenDetectedForSubband[FFT_SUBBANDS];

		float beatCutoffF = 10.0f;

		float bpmEstimates[FFT_SUBBANDS];

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void audioIn(ofSoundBuffer & input);

		int bpm = 120;
		int bpmTapCount = 0;
		float lastBpmTap;
		float bpmTaps[10];



		void handleBpmTap(float &time);

		float currentBpm;
		float currentBpmSetTime;

		int currentBeat;
		int currentBar;

		float barProgress;
		float beatProgress;

		void setBpm(float bpm);

		void updateBeat();
		
	private:



		bool loadScript(std::string path);
};

#endif