//
// KinoMirror - Mirroring and kaleidoscope effect
//
// Copyright (C) 2015 Keijiro Takahashi
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "MyKidoPass.h"
#include "ofMain.h"
#include "myPostProcessing.h"

MyKidoPass::MyKidoPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb, float segments) :
        segments(segments), RenderPass(processor, aspect, arb, "MyKido")
    {

        string fragShaderSrc = STRINGIFY(

                uniform sampler2D tDiffuse;
                uniform float _Offset;
                uniform float _Divisor;
                uniform float _Roll;
                uniform float iTime;

                float random (vec2 st) {
                    return fract(sin(dot(st.xy,
                        vec2(12.9898,78.233))) *
                        43758.5453123);
                }

                void main() {

                    vec2 vUv = gl_TexCoord[0].st;

                    vec2 sc = vUv - 0.5;
                    float phi = atan(sc.y, sc.x);
                    float r = sqrt(dot(sc, sc));

                    // Angular repeating.
                    phi += _Offset;
                    phi = phi - _Divisor * floor(phi / _Divisor);
                    // #if SYMMETRY_ON
                    phi = min(phi, _Divisor - phi);
                    // #endif
                    phi += _Roll - _Offset;

                    // Convert back to the texture coordinate.
                    vec2 uv = vec2(cos(phi), sin(phi)) * r + 0.5;

                    // Reflection at the border of the screen.
                    uv = max(min(uv, 2.0 - uv), -uv);

                    gl_FragColor = texture2D(tDiffuse, uv);

                    

                }
        );
        
    
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShaderSrc);
        shader.linkProgram();
        
    }
    

    void MyKidoPass::render(ofFbo& readFbo, ofFbo& writeFbo)
    {
        writeFbo.begin();
        
        shader.begin();
        
        shader.setUniformTexture("tDiffuse", readFbo.getTexture(), 0);
        shader.setUniform1f("_Offset", 0.0f);
        shader.setUniform1f("_Divisor", PI * 2 / max(segments, 1.0f));

        shader.setUniform1f("_Roll", time / 10.0f);
        shader.setUniform1f("iTime", time);
        
        texturedQuad(0, 0, writeFbo.getWidth(), writeFbo.getHeight());
        
        shader.end();
        writeFbo.end();
    }

    void MyKidoPass::enablePass(float segments, float time)
    {
        processor->addPass([this, segments, time](ofFbo& readFbo, ofFbo& writeFbo) {
            this->setTime(time);
            this->setSegments(segments);
            this->render(readFbo, writeFbo);
        });
    }

    void MyKidoPass::enablePass(float segments)
    { 
        enablePass(segments, ofGetElapsedTimef());
    }

std::function<void(ofFbo&, ofFbo&)> MyKidoPass::getPassFunc(float segments, float time)
{
    return [this, segments, time](ofFbo& readFbo, ofFbo& writeFbo) {
            this->setTime(time);
            this->setSegments(segments);
            this->render(readFbo, writeFbo);
        };
}

std::function<void(ofFbo&, ofFbo&)> MyKidoPass::getPassFunc(float segments)
{
    return getPassFunc(segments, ofGetElapsedTimef());
}