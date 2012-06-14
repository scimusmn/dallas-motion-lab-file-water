#include "config.h"

static configuration config;

configuration & cfg(){
	return config;
};

void configuration::readGeneralConfig(string cfgFile){
	ifstream config(ofToDataPath(cfgFile).c_str());
	while (config.peek()!=EOF) {
		string nextLine;
		getline(config, nextLine);
		vector<string> token=ofSplitString(nextLine, "=\r\n");
		if(token.size()){
			if(token[0]=="WATCH_DIR"){
				watchDir=ofToDataPath(token[1]);
			}
			else if(token[0]=="DESTINATION"){
				dest=token[1];
			}
			else if(token[0]=="SERVER_NAME"){
				serverName=token[1];
			}
			else if(token[0]=="CHECK_FREQUENCY_IN_SECONDS"){
				freq=ofToFloat(token[1]);
			}
			else if(token[0]=="REFRESH_ON_START"){
				refresh=ofToInt(token[1]);
			}
			else if(token[0]=="SERVER_PORT"){
				serverPort=ofToInt(token[1]);
			}
			else if(token[0]=="COMMAND"){
				command=token[1];
			}
			else if(token[0]=="SERVER_ADDRESS"){
				serverAddress=token[1];
			}
			else if(token[0]=="VERBOSE"){
				verbose=ofToInt(token[1]);
			}
		}
	}
	config.close();
}