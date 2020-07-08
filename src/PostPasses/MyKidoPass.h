#pragma once

#include "RenderPass.h"
#include "ofShader.h"

class MyKidoPass : public itg::RenderPass {
public:
    
    typedef shared_ptr<MyKidoPass> Ptr;
    
    MyKidoPass(const ofVec2f& aspect, bool arb, float segments = 20.0f);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo, ofTexture& depth);
    
    float getSegments(){ return segments; }
    void setSegments(float v) { segments = v; }
    
private:
    
    ofShader shader;
    float segments;
    
};