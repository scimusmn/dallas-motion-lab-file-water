//#include "ofMain.h"
#include "testApp.h"
//#include "ofAppGlutWindow.h"
#include "fileAlert.h"

//========================================================================
int main( ){

    //ofAppGlutWindow window;
	//ofSetupOpenGL(&window, 100,100, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp( new testApp());

	//watcher().setup();
	ofSetVerticalSync(true);
	alert().setup();

	while(1){	
		//watcher().checkFolder();
		alert().idle();
	}
}
