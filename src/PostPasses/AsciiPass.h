#pragma once

#include "RenderPass.h"

class AsciiPass : public RenderPass {
public:
    
    typedef shared_ptr<AsciiPass> Ptr;
    
    AsciiPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb, float scale = 10.0);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo);

    void enablePass(float scale);
    std::function<void(ofFbo&, ofFbo&)> getPassFunc(float scale);

      float getScale(){ return scale; }
    void setScale(float v) { scale = v; }
    
private:
    
    ofShader shader;
    ofImage text;

    float scale;

};