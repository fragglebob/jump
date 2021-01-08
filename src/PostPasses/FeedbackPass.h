#pragma once

#include "RenderPass.h"

class FeedbackPass : public itg::RenderPass {
public:
    
    typedef shared_ptr<FeedbackPass> Ptr;
    
    FeedbackPass(const ofVec2f& aspect, bool arb);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo);

    void allocateFbo();
    
private:
    
    ofFbo feedbackFbo;
    
};