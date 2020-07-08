#pragma once

#include "RenderPass.h"
#include "ofShader.h"

class GridShiftPass : public itg::RenderPass {
public:
    
    typedef shared_ptr<GridShiftPass> Ptr;
    
    GridShiftPass(const ofVec2f& aspect, bool arb, float rows = 8.0f);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo, ofTexture& depth);
    
    float getRows(){ return rows; }
    void setRows(float v) { rows = v; }
    
private:
    
    ofShader shader;
    
    float rows;
    
};