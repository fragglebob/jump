//
// Created by rob on 15/05/2020.
//

#include "myPostProcessing.h"
#include "ofMain.h"

void myPostProcessing::resize(unsigned width, unsigned height, bool arb) {
    init(width, height, arb);

    auto passes = getPasses();

    for(auto const& value: passes) {
        value->setAspect(ofVec2f(width, height));
    }
}