//
// Created by rob on 15/05/2020.
//

#ifndef JUMP_MYPOSTPROCESSING_H
#define JUMP_MYPOSTPROCESSING_H

#include "RenderPass.h"
#include "ofCamera.h"

class myPostProcessing : public ofBaseDraws
{
public:
    typedef shared_ptr<myPostProcessing> Ptr;
    
    void init(unsigned width = ofGetWidth(), unsigned height = ofGetHeight(), bool arb = false);
    void begin();
    void begin(ofCamera& cam);
    void end(bool autoDraw = true);
    
    // float rather than int and not const to override ofBaseDraws
    void draw(float x = 0.f, float y = 0.f) const;
    void draw(float x, float y, float w, float h) const;
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    
    void debugDraw();
    
    template<class T>
    shared_ptr<T> createPass()
    {
        shared_ptr<T> pass = shared_ptr<T>(new T(ofVec2f(width, height), arb));
        passes.push_back(pass);
        return pass;
    }
    
    ofTexture& getProcessedTextureReference();
    
    // advanced
    void process(ofFbo& raw, bool hasDepthAsTexture = true);
    
    /**
     * Set flip.
     * Turn on if using ofEasyCam to fix flipping bug.
     */
    void setFlip(bool flip) { this->flip = flip; }
    
    unsigned size() const { return passes.size(); }
    itg::RenderPass::Ptr operator[](unsigned i) const { return passes[i]; }
    vector<itg::RenderPass::Ptr>& getPasses() { return passes; }
    unsigned getNumProcessedPasses() const { return numProcessedPasses; }
    
    ofFbo& getRawRef() { return raw; }

    void resize(unsigned _w, unsigned _h, bool arb);
    
private:
    void process();
    
    unsigned currentReadFbo;
    unsigned numProcessedPasses;
    unsigned width, height;
    bool flip;
    bool arb;
    
    ofFbo raw;
    ofFbo pingPong[2];
    vector<itg::RenderPass::Ptr> passes;
};

#endif //JUMP_MYPOSTPROCESSING_H
