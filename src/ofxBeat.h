//
// Created by rob on 25/04/2020.
//

#ifndef JUMP_OFXBEAT_H
#define JUMP_OFXBEAT_H

#ifndef OFX_BEAT_STANDALONE
#include "ofMain.h"
#endif

#include "fft.h"

#define FFT_BINS 512
#define FFT_SUBBANDS 32
#define ENERGY_HISTORY 43

#define KICK_BAND 0
#define SNARE_BAND 1
#define HIHAT_BAND 2

#define DFLT_BUFFER_SIZE 1024
#define DFLT_FFT_SIZE 512

class ofxBeat {

    float fftSmoothed[FFT_BINS];
    float averageEnergy[FFT_SUBBANDS];
    float fftVariance[FFT_SUBBANDS];
    float beatValueArray[FFT_SUBBANDS];
    float energyHistory[FFT_SUBBANDS][ENERGY_HISTORY];
    float *in_fft;
    float beatValue;
    int historyPos;
    bool fftInit;
#ifndef OFX_BEAT_STANDALONE
    ofSoundPlayer soundtrack;
#endif

    float fftSubbands[FFT_SUBBANDS];
    int bandTimes[3];
    int beatSizes[3];
    float beats[3];

    int buffer_size;
    int fft_size;

    float *magnitude, *phase, *power, *audio_input;
    float *magnitude_average, *magnitude_average_snapshot;

    bool bDetectBeat;

    fft myfft;

    void updateBand(bool,int,int);
    void updateFFT();

public:
    ofxBeat(size_t buffer_size, size_t fft_size);
    ofxBeat() : ofxBeat(DFLT_BUFFER_SIZE, DFLT_FFT_SIZE) { }

    void enableBeatDetect() {bDetectBeat = true;}
    void disableBeatDetect() {bDetectBeat = false;}
    bool isBeat(int subband);
    bool isKick();
    bool isSnare();
    bool isHat();
    bool isBeatRange(int low, int high, int threshold);
    void setBeatValue(float bv) {beatValue = bv;}

    void update(int);
    void audioReceived(const float *const, int, int);
    void audioReceived(ofSoundBuffer & input);
    void audioFill(const float *const, int);
    void audioProcess(int);

    float kick();
    float snare();
    float hihat();
    float getMagnitude();

    float getBand(int);

    int getBufferSize();
};

#endif //JUMP_OFXBEAT_H
