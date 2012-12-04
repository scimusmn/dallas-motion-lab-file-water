#pragma once

#include "ofMain.h"
#include "ofExtended.h"
#include "ofxSystemCall.h"
#include "ofxNetwork.h"

class folderAlert {
protected:
	string dir;
	string command;
	string mapRoot;
	string dest;
	ofSystemCall call;
	ofxTCPClient tcpClient;
	ofxTCPServer tcpServer;
	ofTimer connectTimer,
		checkTimer;
	bool bConnected;
public:
	void idle();
	void checkConnection();
	void setup();
};

folderAlert & alert();