#pragma once

#include "ofMain.h"
#include "ofExtended.h"
#include "ofxSystemCall.h"
#include "ofxNetwork.h"

class folderAlert {
protected:
	string dir;
	string command;
	string dest;
	ofSystemCall call;
	ofxTCPClient tcpClient;
	ofxTCPServer tcpServer;
	ofTimer connectTimer;
	bool bConnected;
public:
	void idle();
	void setup();
};

folderAlert & alert();