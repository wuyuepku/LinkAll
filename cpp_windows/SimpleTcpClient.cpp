#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <WS2tcpip.h>
using namespace std;

const char connect_ip[] = "127.0.0.1";
const int connect_port = 666;
void handleConnect(SOCKET& sClient) {
  char sendData[] = "Hello? Is there anyone?\n";
  send(sClient, sendData, strlen(sendData), 0);
  char recvData[4096];
  int ret = recv(sClient, recvData, sizeof(recvData), 0);
  if(ret>0){
    recvData[ret] = 0x00;
    printf("%s\n", recvData);
  }
}






#pragma comment(lib,"ws2_32.lib")
//using Mingw to compile the program, use -lws2_32 parameter, such as
//g++ ./SimpleTcpClient.cpp -lws2_32 -o SimpleTcpClient.exe ; ./SimpleTcpClient.exe ; rm SimpleTcpClient.exe

int main(int argc, char* argv[]) {
	//initialize WSA
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA wsaData;
	if(WSAStartup(sockVersion, &wsaData)!=0) return 0;

	//create socket
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sClient == INVALID_SOCKET) {
		printf("socket error !\n"); return 0;
	}

	//bind IP port
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(connect_port);
	sin.sin_addr.S_un.S_addr = inet_addr(connect_ip);
	if(connect(sClient, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) {
		printf("connect error !\n");
    closesocket(sClient);
    return 0;
	}

	//hanlde data
  handleConnect(sClient);

	//close
  closesocket(sClient);
	WSACleanup();
	return 0;
}
