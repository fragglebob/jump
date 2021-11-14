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
    s.width = this->aspect.x;
    s.height = this->aspect.y;
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
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        feedbackFbo.draw(0,0, feedbackFbo.getWidth(), feedbackFbo.getHeight());
        readFbo.draw(0,0, readFbo.getWidth(), readFbo.getHeight());
    writeFbo.end();


    feedbackFbo.begin();
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        readFbo.draw(0,0, readFbo.getWidth(), readFbo.getHeight());
    feedbackFbo.end();
}

std::function<void(ofFbo&, ofFbo&)> FeedbackPass::getPassFunc()
{
    return [this](ofFbo& readFbo, ofFbo& writeFbo) {
        this->render(readFbo, writeFbo);
    };
}
void FeedbackPass::enablePass()
{
    processor->addPass([this](ofFbo& readFbo, ofFbo& writeFbo) {
        this->render(readFbo, writeFbo);
    });
}
