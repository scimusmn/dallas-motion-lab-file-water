#include "fileAlert.h"
#include "config.h"

folderAlert alrt;

folderAlert & alert()
{
	return alrt;
}

void folderAlert::idle()
{
	//tcpClient.TCPClient.CheckHost()
	if(tcpClient.isConnected()){
		string str=tcpClient.receive();
		string srcRoot,setName;
		if(str=="<packet>"){
			while(str!="</packet>"){
				//cout << str << endl;
				str=tcpClient.receive();
				vector<string> spl=ofSplitString(str,"=");
				if(spl.size()>1){
					if(cfg().verbose) cout << str << endl;
					if(spl[0]=="root") srcRoot=spl[1];
					else if(spl[0]=="set") setName=spl[1];
					//else if(spl[0]=="map_root") mapRoot=spl[1];
				}
			}
			string cmd=command;
			cmd=cmd.replace(cmd.find("$dest"),5,dest);
			cmd=cmd.replace(cmd.find("$src"),4,"Z:\\");
			size_t it=cmd.find("$name");
			while(it!=string::npos){
				cmd=cmd.replace(it,5,setName);
				it=cmd.find("$name",it+1);
			}
			if(cfg().verbose) cout << cmd << endl;
			cout << "\nBeginning transfer of "<< setName << "\n";
			call.run(cmd);
			long cnt=0;
			ofTimer runTime;
			runTime.set(.1);
			runTime.run();
			cout << "Transferring";
			while(call.isRunning()){
				if(runTime.justExpired()){
					cout << ".";
					cnt++;
					runTime.set(.1);
					runTime.run();
				}
			}

			cout << "\nTransfer took " << cnt/10 <<"."<< cnt%10 <<" seconds"<< endl;
		}
		if(str=="<mapRequest>"){
			while(str!="</mapRequest>"){
				//cout << str << endl;
				str=tcpClient.receive();
				vector<string> spl=ofSplitString(str,"=");
				if(spl.size()>1){
					if(cfg().verbose) cout << str << endl;
					if(spl[0]=="map_root"){
						mapRoot=spl[1];
						string netUse="net use Z: " + cfg().serverName + mapRoot.substr(0,mapRoot.length()-1) + " " + cfg().password + " /user:" + cfg().userName;
						call.run(netUse);
						cout << "Mapping network drive...";
						while(call.isRunning()){
							ofTimer runTime;
							runTime.set(.1);
							runTime.run();
							if(runTime.justExpired()){
								cout << ".";
								runTime.set(.1);
								runTime.run();
							}
						}
						cout << "\nMapped " + cfg().serverName + mapRoot + " to Z:\\" << endl;
					}
				}
			}
		}
	}
	else {
		bConnected=false;
		//tcpClient.close();
		if(connectTimer.justExpired()){
			if((bConnected=tcpClient.setup(cfg().serverAddress,cfg().serverPort))){
				tcpClient.send("<mapRequest />");
				cout << "Connected to TCP server" << endl;
				checkTimer.set(1), checkTimer.run();
				connectTimer.set(1),connectTimer.run();
			}
			else connectTimer.set(1),connectTimer.run();
		}
		
	}
	if(checkTimer.justExpired()){
		if(tcpClient.isConnected()&&tcpClient.send("<connectTest />")==false){
			tcpClient.close();
			connectTimer.set(1),connectTimer.run();
		}
		checkTimer.set(1), checkTimer.run();
	}
}

void folderAlert::setup()
{
	cfg().setup();
	dir=cfg().watchDir;
	command=cfg().command;
	dest=cfg().dest;
	bConnected=false;

	//string netUse="net use Z: " + cfg().serverName + " ";
	//command=command.replace(command.find("$dest"),5,dest);
	//command=command.replace(command.find("$src"),4,dir);

	//tcpServer.setup(11999);

	bConnected=tcpClient.setup(cfg().serverAddress,cfg().serverPort);
	//tcpClient.setMessageDelimiter("\n");

	if(tcpClient.isConnected()){
		tcpClient.send("<mapRequest />");
		cout << "Connected to TCP server" << endl;
		checkTimer.set(1), checkTimer.run();
		//string str=tcpClient.receive();
	}
	
	connectTimer.set(1),connectTimer.run();

	//tcpClient.setVerbose(false);
}