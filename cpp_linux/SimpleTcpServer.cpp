#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include <arpa/inet.h>

const int listning_port = 666;
void handleConnect(int sClient) {
	char recvData[4096];
	int ret = recv(sClient, recvData, sizeof(recvData), 0);
	if(ret > 0) {
		recvData[ret] = 0x00;
		printf("%s\n", recvData);
	}
	const char * sendData = "Hello World!\n";
	send(sClient, sendData, strlen(sendData), 0);
}




//compile the program like this
//g++ ./SimpleTcpServer.cpp -o SimpleTcpServer && sudo ./SimpleTcpServer ; rm SimpleTcpServer

int main(int argc, char* argv[])
{
  int listenfd, connfd;
  struct sockaddr_in servaddr;

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(listning_port);

  //solving the problem of bind error, port already in use
  int on = 1;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

  if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
  }

  if (listen(listenfd, 10) == -1) {
    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
  }

  printf("----listening on port: %d\n", listning_port);

  do {
    if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1) {
      printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
      continue;
    }
    handleConnect(connfd);
    close(connfd);
  } while (0);


  printf("exit\n");
  close(listenfd);
  return 0;
}
