//============================================================================
// Name        : VirtualAddressAccess.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "AccessVirtualMemory.h"
#include <unistd.h>
using namespace std;

int main() {
	float phase=0;
	float radius=0;
	char buffer[100];
	memset(buffer,0,100);
	AccessVirtualMemory demoMovingObject("virtual","DemoMovingObject");
	while(true){
		demoMovingObject.ReadData(buffer,0x08052374,8);
		memcpy((char*)&radius,buffer,4);
		memcpy((char*)&phase,buffer+4,4);
		printf("%f\t%f\n",phase,radius);
		sleep(1);
	}
	return 0;
}
