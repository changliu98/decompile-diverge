int connectToServer(int *pSockConnection, char *serverIP, int serverPort)
{
 struct sockaddr_in sAddr;

 *pSockConnection = socket(2, 1, 0);
 if (*pSockConnection == -1)
  return -1;

 sAddr.sin_family = 2;
 sAddr.sin_addr.s_addr = inet_addr(serverIP);
 sAddr.sin_port = htons(serverPort);

 if (connect(*pSockConnection, (struct sockaddr *)&sAddr, sizeof(sAddr)) == -1)
 {
  close(*pSockConnection);
  return -1;
 }

 return 0;
}