/*
 * AccessVirtualMemory.cpp
 *
 *  Created on: Jun 14, 2021
 *      Author: Minh
 */

#include "AccessVirtualMemory.h"

AccessVirtualMemory::AccessVirtualMemory(string machineName,string processName) {
	// TODO Auto-generated constructor stub
	this->processName=processName;
	this->machineName=machineName;
	sourceMemory="";
	GetNodeId();
	GetPID();
	GetSourceMemory();
}

AccessVirtualMemory::~AccessVirtualMemory() {
	// TODO Auto-generated destructor stub
}

int AccessVirtualMemory::GetNodeId(){
	nodeId = netmgr_strtond(machineName.c_str(), NULL);
	printf("%s nodeid: %d\n",machineName.c_str(), nodeId);
	return nodeId;
}

int AccessVirtualMemory::GetPID(){
	char tmp[512];
	int chid=0;
	char* command=new char[50];
	sprintf(command,"pidin -n %s -p %s -F '%s' ",machineName.c_str(),processName.c_str(),"%a");
	std::cout<<command<<std::endl;
	FILE* fp = popen(command,"r");
	fscanf(fp, "%s %d",tmp,&PID);
	printf("ppi51 pid %d\n", PID);
	pclose(fp);
	return PID;
}

string AccessVirtualMemory::GetSourceMemory(){
	char s[50];
	if(PID!=0){
		sprintf(s, "//proc//%d//as", PID);
		std::cout << s << std::endl;
		sourceMemory = s;
		std::cout << "Source memory: " << sourceMemory << std::endl;
		return sourceMemory;
	}else{
		sourceMemory="";
		std::cout<<"Source does not exist"<<std::endl;
		return "";
	}
}

void AccessVirtualMemory::ReadData(char* buffer,long long address,int size){
	if(sourceMemory=="")return;
	FILE* f= fopen(sourceMemory.c_str(),"r");
	fseek(f,address,SEEK_SET);
	fread(buffer,size,1,f);
	fclose(f);
}
