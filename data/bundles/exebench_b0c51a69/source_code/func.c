#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

int connectToServer(int *pSockConnection, char* serverIP, int serverPort)
{
  struct sockaddr_in sAddr;

  if((*pSockConnection=socket(PF_INET,SOCK_STREAM,0))==-1)
  {
    return -1;
  }
  sAddr.sin_family=AF_INET;
  sAddr.sin_addr.s_addr=inet_addr(serverIP);
  sAddr.sin_port=htons(serverPort);
  if(connect(*pSockConnection,(struct sockaddr*)&sAddr,sizeof(sAddr))==-1)
  {
     close(*pSockConnection);
     return -1;
  }
  return 0;
}
