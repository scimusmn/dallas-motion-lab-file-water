#include "fileWatcher.h"
#include "config.h"

folderWatcher wtch;

folderWatcher & watcher()
{
	return wtch;
}

void folderWatcher::checkFolder()
{
	if(checkTimer.justExpired()){
		//cout << "Checking...\n";
		checkTimer.set(freq);
		checkTimer.run();
		call.run("dir \""+dir+"\"");
		while(call.isRunning());
		for(int i=0; i<call.outputLines(); i++){
			vector<string> spl= ofSplitString(call[i]," ");
			if(spl.size()>=5){
				if(spl[3]=="<DIR>"){
					map<string,string>::iterator it;
					if((it=fileDates.find(spl[4]))!=fileDates.end()){
						if(it->second!=spl[0]+spl[1]+spl[2]){
							fileDates[spl[4]]=spl[0]+spl[1]+spl[2];
							size_t it=command.find("$name");
							string newCmd=command;
							while(it!=string::npos){
								newCmd=newCmd.replace(it,5,spl[4]);
								it=command.find("$name",it+1);
							}
							//cout << newCmd<<endl;
							call.run(newCmd,true);
						}
					}
					else if(spl[4]!="."&&spl[4]!=".."){
						fileDates[spl[4]]=spl[0]+spl[1]+spl[2];
						//call.run_not_threaded(
						size_t it=command.find("$name");
						string newCmd=command;
						while(it!=string::npos){
							newCmd=newCmd.replace(it,5,spl[4]);
							it=command.find("$name",it+1);
						}
						//cout << newCmd << endl;
						call.run(newCmd,true);
					}
				}
			}
			//cout << call[i] << endl;
		}
	}
}

void folderWatcher::setup()
{
	cfg().setup();
	dir=cfg().watchDir;
	freq=cfg().freq;
	command=cfg().command;
	dest=cfg().dest;
	size_t it;
	command=command.replace(command.find("$dest"),5,dest);
	command=command.replace(command.find("$src"),4,dir);
	checkTimer.set(freq);
	checkTimer.run();
	call.run("dir \""+dir+"\"");
	while(call.isRunning());
	for(int i=0; i<call.outputLines(); i++){
		vector<string> spl= ofSplitString(call[i]," ");
		if(spl.size()>=5){
			if(spl[3]=="<DIR>"){
				if(spl[4]!="."&&spl[4]!=".."){
					fileDates[spl[4]]=spl[0]+spl[1]+spl[2];
					cout << spl[4] << endl;
				}
			}
		}
	}
}