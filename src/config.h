#pragma once

#include "ofMain.h"
#include "ofExtended.h"
#include "../../dallasEng/dallasEng.h"

struct configuration {
	string watchDir;
	string dest;
	double freq;
	bool refresh;
	string command;
	double waitTime;
	string serverAddress;
	string serverName;
	bool verbose;
	int serverPort;
	void readGeneralConfig(string cfgFile);
	configuration(){
		ofEnableDataPath();
	}
	void setup(){
		readGeneralConfig("config.txt");
	}
};

configuration & cfg();