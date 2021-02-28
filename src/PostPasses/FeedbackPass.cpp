#include "FeedbackPass.h"
#include "ofMain.h"
#include "myPostProcessing.h"

FeedbackPass::FeedbackPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb) :
         RenderPass(processor, aspect, arb, "Feedback")
{
    
    this->allocateFbo();
    
}

void FeedbackPass::allocateFbo()
{
    ofFbo::Settings s;
    s.width = ofNextPow2(this->aspect.x);
    s.height = ofNextPow2(this->aspect.y);
    s.textureTarget = GL_TEXTURE_2D;
    s.internalformat = GL_RGBA;
    // s.numSamples = 4;

    feedbackFbo.allocate(s);

    feedbackFbo.begin();
    ofClear(0,0,0,255);
    feedbackFbo.end();
}

void FeedbackPass::render(ofFbo& readFbo, ofFbo& writeFbo)
{
    writeFbo.begin();
        ofClear(0,0,0,255);

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetDepthTest(false);
        feedbackFbo.draw(0,0, feedbackFbo.getWidth(), feedbackFbo.getHeight());
        ofSetDepthTest(true);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
        readFbo.draw(0,0, readFbo.getWidth(), readFbo.getHeight());
    writeFbo.end();


    feedbackFbo.begin();
        ofSetDepthTest(false);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        readFbo.draw(0,0, readFbo.getWidth(), readFbo.getHeight());
        ofSetDepthTest(true);
    feedbackFbo.end();
}


void FeedbackPass::enablePass()
{
    processor->addPass([this](ofFbo& readFbo, ofFbo& writeFbo) {
        this->render(readFbo, writeFbo);
    });
}
