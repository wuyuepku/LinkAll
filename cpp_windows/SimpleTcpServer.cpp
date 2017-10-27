#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>
using namespace std;

const int listning_port = 666;
void handleConnect(SOCKET& sClient) {
	char recvData[4096];
	int ret = recv(sClient, recvData, sizeof(recvData), 0);
	if(ret > 0) {
		recvData[ret] = 0x00;
		printf("%s\n", recvData);
	}
	const char * sendData = "Hello World!\n";
	send(sClient, sendData, strlen(sendData), 0);
}





#pragma comment(lib,"ws2_32.lib")
//using Mingw to compile the program, use -lws2_32 parameter, such as
//g++ ./SimpleTcpServer.cpp -lws2_32 -o SimpleTcpServer.exe ; ./SimpleTcpServer.exe ; rm SimpleTcpServer.exe

int main(int argc, char* argv[]) {
	//initialize WSA
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA wsaData;
	if(WSAStartup(sockVersion, &wsaData)!=0) return 0;

	//create socket
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(slisten == INVALID_SOCKET) {
		printf("socket error !\n"); return 0;
	}

	//bind IP port
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(listning_port);
	sin.sin_addr.S_un.S_addr = INADDR_ANY; //INADDR_ANY, INADDR_LOOPBACK, INADDR_BROADCAST, INADDR_NONE
	if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) {
		printf("bind error !\n"); return 0;
	}

	//start listening
	if (listen(slisten, 5) == SOCKET_ERROR) {
		printf("listen error !\n"); return 0;
	}

	//receive data
	SOCKET sClient;
  sockaddr_in remoteAddr;
  int nAddrlen = sizeof(remoteAddr);
	do {
		printf("----listening on port: %d\n", listning_port);
		sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
		if(sClient == INVALID_SOCKET) {
			printf("accept error !");
			continue;
		}
		printf("----received a connect on: %s\n", inet_ntoa(remoteAddr.sin_addr));
		handleConnect(sClient);
		closesocket(sClient);
	} while (0);

	//close
	closesocket(slisten);
	WSACleanup();
	return 0;
}
