/*
 * AccessVirtualMemory.h
 *
 *  Created on: Jun 14, 2021
 *      Author: Minh
 */

#ifndef ACCESSVIRTUALMEMORY_H_
#define ACCESSVIRTUALMEMORY_H_
#include <iostream>
#include <string>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/dcmd_chr.h>
#include <stdio.h>
using namespace std;

class AccessVirtualMemory {
public:
	AccessVirtualMemory(string machineName,string processName);
	virtual ~AccessVirtualMemory();
	int GetNodeId();
	int GetPID();
	string GetSourceMemory();
	void ReadData(char* buffer,long long address,int size);
private:
	string processName;
	string machineName;
	string sourceMemory;
	int nodeId;
	int PID;
};

#endif /* ACCESSVIRTUALMEMORY_H_ */
