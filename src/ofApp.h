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
#include "Gist.h"
#include "BeatDetektor.h"

class ofApp : public ofBaseApp {

	public:

		ofApp() : gist(1024, 44100), ofBaseApp()
		{

		};

		sol::state lua;
		ofSol solHelper;

        ofLight light;
        ofLight amb;
        myPostProcessing post;

        ofxBeat beat;
        ofSoundStream soundStream;

		MidiMix midiMix;

		Gist<float> gist;

		float gist_rms;
		float gist_peak;
		float gist_zcr;

		float gist_spec_cent;
		float gist_spec_crest;
		float gist_spec_flat;
		float gist_spec_rolloff;
		float gist_spec_kurtosis;

		std::vector<float> gist_mel_spec;

		BeatDetektor detektor;

		std::time_t modTimes[10];
		bool errors[10];

		MyKidoPass::Ptr kaleido;
		BloomPass::Ptr bloom;
		GridShiftPass::Ptr grid;
		SliceWavePass::Ptr wave;

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