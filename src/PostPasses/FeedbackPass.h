#pragma once

#include "RenderPass.h"

class FeedbackPass : public RenderPass {
public:
    
    typedef shared_ptr<FeedbackPass> Ptr;
    
    FeedbackPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo);

    void allocateFbo();

    void enablePass();
    std::function<void(ofFbo&, ofFbo&)> getPassFunc();
    
private:
    
    ofFbo feedbackFbo;
    
};