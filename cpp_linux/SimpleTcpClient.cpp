#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include <arpa/inet.h>

const char connect_ip[] = "127.0.0.1";
const int connect_port = 666;
void handleConnect(int sClient) {
  char sendData[] = "Hello? Is there anyone?\n";
  send(sClient, sendData, strlen(sendData), 0);
  char recvData[4096];
  int ret = recv(sClient, recvData, sizeof(recvData), 0);
  if(ret>0){
    recvData[ret] = 0x00;
    printf("%s\n", recvData);
  }
}




//compile the program like this
//g++ ./SimpleTcpClient.cpp -o SimpleTcpClient && sudo ./SimpleTcpClient ; rm SimpleTcpClient

int main(int argc, char* argv[]) {
  int sockfd;
  struct sockaddr_in servaddr;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(connect_port);
  //servaddr.sin_addr = inet_addr(connect_ip);
  if( inet_pton(AF_INET, connect_ip, &servaddr.sin_addr) <= 0) {
    printf("inet_pton error for %s\n", connect_ip);
    exit(0);
  }

  if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
  }

  handleConnect(sockfd);

  close(sockfd);
  exit(0);
}
