//
// Created by rob on 15/05/2020.
//

#include "myPostProcessing.h"
#include "ofMain.h"


void cleanFbo(ofFbo& fbo) {
    fbo.begin(OF_FBOMODE_NODEFAULTS);
    // ofClear(0,0,0,0);
    glClearColor(0,0,0,0);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // ofClearAlpha();
    fbo.end();
}

void myPostProcessing::init(unsigned width, unsigned height, bool arb)
{
    this->width = width;
    this->height = height;
    this->arb = arb;
    
    ofFbo::Settings s;

    s.internalformat = GL_RGBA;
    
    if (arb)
    {
        s.width = width;
        s.height = height;
        s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
    }
    else
    {
        s.width = ofNextPow2(width);
        s.height = ofNextPow2(height);
        s.textureTarget = GL_TEXTURE_2D;
    }
    
    // s.numSamples = 4;

    // no need to use depth for ping pongs
    for (int i = 0; i < 2; ++i)
    {
        pingPong[i].allocate(s);
    }

    // s.numSamples = 0;
    
    s.useDepth = true;
    s.depthStencilInternalFormat = GL_DEPTH_COMPONENT24;
    s.depthStencilAsTexture = true;
    raw.allocate(s);
    
    numProcessedPasses = 0;
    currentReadFbo = 0;
    flip = true;
}

void myPostProcessing::begin()
{
    raw.begin(OF_FBOMODE_NODEFAULTS);
    
    // ofMatrixMode(OF_MATRIX_PROJECTION);
    ofPushMatrix();
    
    // ofMatrixMode(OF_MATRIX_MODELVIEW);
    ofPushMatrix();
    
    ofViewport(0, 0, raw.getWidth(), raw.getHeight());
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    ofPushStyle();
    glPushAttrib(GL_ENABLE_BIT);
}

void myPostProcessing::begin(ofCamera& cam)
{
    // update camera matrices
    cam.begin();
    cam.end();
    
    raw.begin(OF_FBOMODE_NODEFAULTS);
    
    // ofMatrixMode(OF_MATRIX_PROJECTION);
    ofPushMatrix();
    ofLoadMatrix(cam.getProjectionMatrix(ofRectangle(0, 0, width, height)));
    
    // ofMatrixMode(OF_MATRIX_MODELVIEW);
    ofPushMatrix();
    ofLoadMatrix(cam.getModelViewMatrix());
    
    ofViewport(0, 0, raw.getWidth(), raw.getHeight());
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    ofPushStyle();
    glPushAttrib(GL_ENABLE_BIT);
}

void myPostProcessing::end(bool autoDraw)
{
    glPopAttrib();
    ofPopStyle();
    
    ofViewport(0, 0, ofGetWidth(), ofGetHeight());
    
    // ofMatrixMode(OF_MATRIX_PROJECTION);
    ofPopMatrix();
    
    // ofMatrixMode(OF_MATRIX_MODELVIEW);
    ofPopMatrix();
    
    raw.end();
    
    ofPushStyle();
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    ofSetColor(255, 255, 255);
    ofEnableAlphaBlending();
    process();
    if (autoDraw) draw();
    glPopAttrib();
    ofPopStyle();

    for (int i = 0; i < 2; ++i)
    {
        cleanFbo(pingPong[i]);
    }
}

void myPostProcessing::debugDraw()
{
    raw.getTexture().draw(10, 10, 300, 300);
    raw.getDepthTexture().draw(320, 10, 300, 300);
    pingPong[currentReadFbo].draw(630, 10, 300, 300);
}

void myPostProcessing::draw(float x, float y) const
{
    draw(x, y, width, height);
}

void myPostProcessing::draw(float x, float y, float w, float h) const
{
    if (flip)
    {
        ofPushMatrix();
        ofTranslate(x, y + h, 0);
        ofScale(1, -1, 1);
    }
    else glTranslatef(x, y, 0);
    if (numProcessedPasses == 0) raw.draw(0, 0, w, h);
    else pingPong[currentReadFbo].draw(0, 0, w, h);
    if (flip) ofPopMatrix();
}

ofTexture& myPostProcessing::getProcessedTextureReference()
{
    if (numProcessedPasses) return pingPong[currentReadFbo].getTexture();
    else return raw.getTexture();
}


// need to have depth enabled for some fx
void myPostProcessing::process(ofFbo& raw, bool hasDepthAsTexture)
{
    numProcessedPasses = 0;
    for (int i = 0; i < passes.size(); ++i)
    {
        if (passes[i]->getEnabled())
        {
            if (arb && !passes[i]->hasArbShader()) ofLogError() << "Arb mode is enabled but pass " << passes[i]->getName() << " does not have an arb shader.";
            else
            {
                cleanFbo(pingPong[1 - currentReadFbo]);
                if (hasDepthAsTexture)
                {
                    if (numProcessedPasses == 0) passes[i]->render(raw, pingPong[1 - currentReadFbo], raw.getDepthTexture());
                    else passes[i]->render(pingPong[currentReadFbo], pingPong[1 - currentReadFbo], raw.getDepthTexture());
                }
                else
                {
                    if (numProcessedPasses == 0) passes[i]->render(raw, pingPong[1 - currentReadFbo]);
                    else passes[i]->render(pingPong[currentReadFbo], pingPong[1 - currentReadFbo]);
                }
                currentReadFbo = 1 - currentReadFbo;
                numProcessedPasses++;
            }
        }
    }
}

void myPostProcessing::process()
{
    process(raw);
}

void myPostProcessing::resize(unsigned width, unsigned height, bool arb) {
    init(width, height, arb);

    auto passes = getPasses();

    for(auto const& value: passes) {
        value->setAspect(ofVec2f(width, height));
    }
}