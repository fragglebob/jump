#include "MatrixPass.h"
#include "ofMain.h"
#include "myPostProcessing.h"

MatrixPass::MatrixPass(myPostProcessing* processor, const ofVec2f& aspect, bool arb) :
         RenderPass(processor, aspect, arb, "Matrix")
{


    string fragShaderSrc = STRINGIFY(

        uniform sampler2D tDiffuse;
       
        uniform mat3 transform;

        void main() {

            vec3 uv = vec3(gl_TexCoord[0].st - 0.5, 1);

            uv *= transform;
            uv += 0.5;
            
            gl_FragColor = texture2D(tDiffuse, fract(uv.xy));
        }
    );
    

    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragShaderSrc);
    shader.linkProgram();

    matrix.set(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );
    
}



void MatrixPass::render(ofFbo& readFbo, ofFbo& writeFbo)
{



    writeFbo.begin();

        shader.begin();
        
        shader.setUniformTexture("tDiffuse", readFbo.getTexture(), 1);

        shader.setUniformMatrix3f("transform", matrix, 1);

        texturedQuad(0, 0, writeFbo.getWidth(), writeFbo.getHeight());


        
        shader.end();
        
    writeFbo.end();



}

void MatrixPass::setMatrix(float a, float b, float c, float d, float e, float f)
{
    matrix.set(a, b, c, d, e, f, 0, 0, 1);
}


void MatrixPass::enablePass(float a, float b, float c, float d, float e, float f)
{
    processor->addPass([this, a, b, c, d, e, f](ofFbo& readFbo, ofFbo& writeFbo) {
        this->setMatrix(a, b, c, d, e, f);
        this->render(readFbo, writeFbo);
    });
}
