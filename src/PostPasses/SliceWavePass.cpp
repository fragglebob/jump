#include "SliceWavePass.h"
#include "ofMain.h"

SliceWavePass::SliceWavePass(const ofVec2f& aspect, bool arb, float segments) :
        segments(segments), RenderPass(aspect, arb, "SliceWave")
    {
        
        string fragShaderSrc = STRINGIFY(

                uniform sampler2D tDiffuse;
                uniform float segments;
                uniform float iTime;

                float random (vec2 st) {
                    return fract(sin(dot(st.xy,
                        vec2(12.9898,78.233))) *
                        43758.5453123);
                }

                void main() {

                    vec2 uv = gl_TexCoord[0].st;
                    
                    //uv.x += fract(iTime);
                    
                    float index = floor(uv.x * segments) / 20.;
                    
                    uv.y -= sin(iTime + index * 5.) / 10.;
                    uv.y = fract(abs(uv.y));
                    //uv.y -= ((fract(iTime + index) * 2.) - 1.) / 10.;

                    // Output to screen
                    gl_FragColor = texture2D(tDiffuse, uv);
                }
        );
        
    
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShaderSrc);
        shader.linkProgram();
        
    }
    

    void SliceWavePass::render(ofFbo& readFbo, ofFbo& writeFbo, ofTexture& depthTex)
    {
        writeFbo.begin();
        
        
        shader.begin();
        
        shader.setUniformTexture("tDiffuse", readFbo.getTexture(), 0);
        shader.setUniform1f("segments", segments);
        shader.setUniform1f("iTime", ofGetElapsedTimef());
        
        texturedQuad(0, 0, writeFbo.getWidth(), writeFbo.getHeight());
        
        shader.end();
        writeFbo.end();
    }