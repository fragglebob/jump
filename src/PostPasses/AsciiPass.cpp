#include "AsciiPass.h"
#include "ofMain.h"
#include "myPostProcessing.h"

AsciiPass::AsciiPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb, float scale) :
         scale(scale), RenderPass(processor, aspect, arb, "Ascii")
{


    string fragShaderSrc = STRINGIFY(

        uniform sampler2D tDiffuse;
        uniform sampler2D tText;

        uniform vec2 resolution;

        uniform float chars;
        uniform float scale;

        float gray(vec3 c){
            return c.x*0.299 + c.y*0.587 + c.z*0.114;
        }

        void main() {

            vec2 uv = gl_TexCoord[0].st;

            vec2 st = floor(uv*resolution/scale) * scale / resolution;

            float val = gray(texture2D(tDiffuse, st).rgb);
            val = clamp(val, 0., 1.) - 1e-5;

            vec2 tuv = mod(uv*resolution, scale) / scale;
            
            tuv.x *= 1.0 / chars;
            tuv.x += floor(val*chars)* (1.0 / chars);
    
            float res = 1.0 - texture2D(tText, tuv).r;
            
            gl_FragColor = texture2D(tDiffuse, uv) * res;
        }
    );
    

    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShaderSrc);
    shader.linkProgram();

    text.load("text.png");
    // textTexture = text.getTexture();
    
}



void AsciiPass::render(ofFbo& readFbo, ofFbo& writeFbo)
{

    ofTexture readTexture = readFbo.getTexture();
    // ofTexture tT = text.getTexture();

    // rT.bind(7);
    // tT.bind(5);

    // readTexture.bind(1);
    // text.bind(2);

    writeFbo.begin();

        shader.begin();
        
        shader.setUniformTexture("tDiffuse", readTexture, 1);
        shader.setUniformTexture("tText", text.getTexture(), 2);

        shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());

        shader.setUniform1f("chars", 9);

        shader.setUniform1f("scale", scale);
        

        texturedQuad(0, 0, writeFbo.getWidth(), writeFbo.getHeight());


        
        shader.end();
        
    writeFbo.end();


        // rT.unbind(1);
        // tT.unbind(2);

}


void AsciiPass::enablePass(float scale)
{
    processor->addPass([this, scale](ofFbo& readFbo, ofFbo& writeFbo) {
        this->setScale(scale);
        this->render(readFbo, writeFbo);
    });
}
