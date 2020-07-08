//
// Created by rob on 15/05/2020.
//

#ifndef JUMP_MYPOSTPROCESSING_H
#define JUMP_MYPOSTPROCESSING_H

#include "ofxPostProcessing.h"

class myPostProcessing : public ofxPostProcessing {
public:
    void resize(unsigned _w, unsigned _h, bool arb);
};

#endif //JUMP_MYPOSTPROCESSING_H
