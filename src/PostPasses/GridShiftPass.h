#pragma once

#include "RenderPass.h"
#include "ofShader.h"

class GridShiftPass : public RenderPass {
public:
    
    typedef shared_ptr<GridShiftPass> Ptr;
    
    GridShiftPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb, float rows = 8.0f);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo);
    
    float getRows(){ return rows; }
    void setRows(float v) { rows = v; }

    void enablePass(float rows);
    
private:
    
    ofShader shader;
    
    float rows;
    
};