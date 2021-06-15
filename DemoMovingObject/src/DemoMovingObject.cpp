//============================================================================
// Name        : DemoMovingObject.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <unistd.h>
#include "inet_sockets.h"
using namespace std;

#define PI 3.14

float radius=0;//km
float phase=0;//degree
float test=1.15;
float R0=50;
float O1_B=120;
float O1_R=70;

typedef struct TcpServer {
	int socketfd;
	int connfd;
	int port;
	TcpServer(int p) {
		socketfd = -1;
		connfd = -1;
		port = p;
	}
}TcpServer;

void Cal(float phiIn,float radiusIn,float* retPhi,float* retRadius){
	float phi_d=(O1_B/180.0)*PI;
	float radius_d=O1_R;
	float r0_sinphi0= radiusIn*sin(phiIn)+radius_d*sin(phi_d);
	float r0_cosphi0= radiusIn*cos(phiIn)+radius_d*cos(phi_d);
	float tanphi0=r0_sinphi0/r0_cosphi0;
	*retPhi= atan(tanphi0);
	*retRadius= r0_sinphi0/sin(*retPhi);
}

void StartMoving(){
	float movingAngle= 2*asin(R0/2/O1_R);
	float deltaAlpha= 1.0/O1_R;
	float startAngle=(-60.0/180.0)*PI;
	int step= movingAngle/deltaAlpha;
	int direct=1;
	float currentAngle= startAngle;
	while(true){
		currentAngle+=(direct*deltaAlpha);
		if(currentAngle>startAngle+movingAngle){
			direct=-1;
			std::cout<<"Change direct to backward"<<std::endl;
		}
		else if(currentAngle<startAngle){
			direct=1;
			std::cout<<"Change direct to forward"<<std::endl;
		}
		Cal(currentAngle,O1_R,&phase,&radius);
		std::cout<<"Phase:"<<phase<<"  Radius:"<<radius<<std::endl;
		sleep(1);
	}
}

int TcpClient(int& sock){
	int valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5555);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "10.61.153.62", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	send(sock , hello , strlen(hello) , 0 );
	return 1;
}

int main() {
	StartMoving();
//	int sock=0;
//	TcpClient(sock);
//	char buffer[1024] = { 0 };
//	send(sock , buffer , 5 , 0 );

	return -1;
}
