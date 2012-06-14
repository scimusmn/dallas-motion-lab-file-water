#include "fileAlert.h"
#include "config.h"

folderAlert alrt;

folderAlert & alert()
{
	return alrt;
}

void folderAlert::idle()
{
	/*if(!bConnected){
		if((bConnected=tcpClient.setup(cfg().serverAddress,11999))){
			tcpClient.send("ping");
			cout << "here" << endl;
		}
	}
	else{
		if(tcpClient.send("ping 2")){
		/*string str=tcpClient.receive();
		if(str.length()){
			size_t it=command.find("$name");
			string newCmd=command;
			while(it!=string::npos){
				newCmd=newCmd.replace(it,5,str);
				it=command.find("$name",it+1);
			}
			//cout << newCmd<<endl;
			//call.run(newCmd,true);
		}
		}
		else bConnected=false;
	}*/

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
				}
			}
			string cmd=command;
			cmd=cmd.replace(cmd.find("$dest"),5,dest);
			cmd=cmd.replace(cmd.find("$src"),4,cfg().serverName+srcRoot);
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
			//cout << srcRoot << setName<< " >> " <<dest << setName;
		}
		
	}
	else {
		if(connectTimer.justExpired()){
			if((bConnected=tcpClient.setup(cfg().serverAddress,cfg().serverPort))){
				tcpClient.send("connected");
			}
			else connectTimer.set(1),connectTimer.run();
		}
		
	}
}

void folderAlert::setup()
{
	cfg().setup();
	dir=cfg().watchDir;
	command=cfg().command;
	dest=cfg().dest;
	bConnected=false;
	//command=command.replace(command.find("$dest"),5,dest);
	//command=command.replace(command.find("$src"),4,dir);

	//tcpServer.setup(11999);

	bConnected=tcpClient.setup(cfg().serverAddress,cfg().serverPort);
	//tcpClient.setMessageDelimiter("\n");

	if(tcpClient.isConnected()){
		tcpClient.send("connected");
		//string str=tcpClient.receive();
	}
	
	connectTimer.set(1),connectTimer.run();

	tcpClient.setVerbose(false);
}