#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(){
	ofAppGLFWWindow window;  
	ofSetupOpenGL(&window, 1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
