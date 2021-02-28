#include "GridShiftPass.h"
#include "ofMain.h"
#include "myPostProcessing.h"

GridShiftPass::GridShiftPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb, float rows) :
        rows(rows), RenderPass(processor, aspect, arb, "GridShift")
    {
        
        string fragShaderSrc = STRINGIFY(

                uniform sampler2D tDiffuse;
                uniform float rows;
                uniform float iTime;

                float random (vec2 st) {
                    return fract(sin(dot(st.xy,
                        vec2(12.9898,78.233))) *
                        43758.5453123);
                }

                void main() {
                    vec2 vUv = gl_TexCoord[0].st;

                    vec2 uv2 = floor(vUv * rows) / rows;
                    vec2 uvOffset = fract(vUv * rows);
                    
                    float gridPoint = floor(random(uv2) * rows * rows + iTime);
                    
                    vec2 startPos = vec2(floor(gridPoint / rows), mod(gridPoint, rows));
                    
                    startPos += uvOffset;
                    startPos = fract(startPos / rows);

                    gl_FragColor = texture2D(tDiffuse, startPos);

                }
        );
        
    
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShaderSrc);
        shader.linkProgram();
        
    }
    

    void GridShiftPass::render(ofFbo& readFbo, ofFbo& writeFbo)
    {
        writeFbo.begin();
        
        
        shader.begin();
        
        shader.setUniformTexture("tDiffuse", readFbo.getTexture(), 0);
        shader.setUniform1f("rows", rows);
        shader.setUniform1f("iTime", ofGetElapsedTimef());
        
        texturedQuad(0, 0, writeFbo.getWidth(), writeFbo.getHeight());
        
        shader.end();
        writeFbo.end();
    }

void GridShiftPass::enablePass(float rows)
{
    processor->addPass([this, rows](ofFbo& readFbo, ofFbo& writeFbo) {
        this->setRows(rows);
        this->render(readFbo, writeFbo);
    });
}