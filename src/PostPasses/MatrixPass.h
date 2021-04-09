#pragma once

#include "RenderPass.h"

class MatrixPass : public RenderPass {
public:
    
    typedef shared_ptr<MatrixPass> Ptr;
    
    MatrixPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb);
    
    void render(ofFbo& readFbo, ofFbo& writeFbo);

    void enablePass(float a, float b, float c, float d, float e, float f);

    void setMatrix(float a, float b, float c, float d, float e, float f);

    
private:
    
    ofShader shader;

    ofMatrix3x3 matrix;

};