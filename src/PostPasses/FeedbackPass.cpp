#include "FeedbackPass.h"
#include "ofMain.h"

FeedbackPass::FeedbackPass(const ofVec2f& aspect, bool arb) :
         RenderPass(aspect, arb, "Feedback")
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

        // 
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetDepthTest(false);
        feedbackFbo.draw(0,0, feedbackFbo.getWidth(), feedbackFbo.getHeight());
        ofSetDepthTest(true);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        // ofEnableBlendMode(OF_BLENDMODE_DISABLED);

            readFbo.draw(0,0, readFbo.getWidth(), readFbo.getHeight());


            // feedbackFbo.draw(0,0, 500, 500);


    writeFbo.end();









    feedbackFbo.begin();

    // ofClear(0,0,0,0);
// ofSetDepthTest(false);
//     ofEnableBlendMode(OF_BLENDMODE_DISABLED);

//     ofPushStyle();
//     glPushAttrib(GL_ENABLE_BIT);
//     glDisable(GL_LIGHTING);
//     ofSetColor(255, 255, 255);
ofSetDepthTest(false);
glEnable(GL_BLEND);
glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
// ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    readFbo.draw(0,0, readFbo.getWidth(), readFbo.getHeight());
    // ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//     glPopAttrib();
//     ofPopStyle();
ofSetDepthTest(true);
    feedbackFbo.end();








    
}