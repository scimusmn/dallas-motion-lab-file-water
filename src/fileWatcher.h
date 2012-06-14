#pragma once

//#include "ofMain.h"
#include "ofExtended.h"
#include "ofxSystemCall.h"

class folderWatcher {
protected:
	string dir;
	string command;
	string dest;
	ofSystemCall call;
	double freq;
	ofTimer checkTimer;
	map<string,string> fileDates;
public:
	void checkFolder();
	void setup();
};

folderWatcher & watcher();