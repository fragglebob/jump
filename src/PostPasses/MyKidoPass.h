#pragma once

#include "RenderPass.h"
#include "ofShader.h"

class MyKidoPass : public RenderPass {
public:
    
    typedef shared_ptr<MyKidoPass> Ptr;
    
    MyKidoPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb, float segments = 20.0f);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo);
    
    float getSegments(){ return segments; }
    void setSegments(float v) { segments = v; }

    bool getTime(){ return time; }
    void setTime(float t) { time = t; }

    void enablePass(float segments, float time);
    void enablePass(float segments);
    
private:
    
    ofShader shader;
    float time;
    float segments;
    
};