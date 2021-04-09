#pragma once

#include "RenderPass.h"
#include "ofShader.h"

class SliceWavePass : public RenderPass {
public:
    
    typedef shared_ptr<SliceWavePass> Ptr;
    
    SliceWavePass(myPostProcessing* processor, const ofVec2f& aspect, bool arb, float segments = 20.0f);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo);
    
    float getSegments(){ return segments; }
    void setSegments(float v) { segments = v; }

    void enablePass(float segments);
    std::function<void(ofFbo&, ofFbo&)> getPassFunc(float segments);
    
private:
    
    ofShader shader;
    float segments;
    
};