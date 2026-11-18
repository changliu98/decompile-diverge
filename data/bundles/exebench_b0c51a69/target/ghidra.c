int connectToServer(int *pSockConnection,char *serverIP,int serverPort)

{
  int iVar1;
  sockaddr_in sAddr;
  int serverPort_local;
  char *serverIP_local;
  int *pSockConnection_local;
  int local_c;
  
  iVar1 = socket(2,1,0);
  *pSockConnection = iVar1;
  if (iVar1 == -1) {
    local_c = -1;
  }
  else {
    sAddr.sin_family = 2;
    sAddr.sin_addr.s_addr = inet_addr(serverIP);
    sAddr.sin_port = htons((uint16_t)serverPort);
    iVar1 = connect(*pSockConnection,(sockaddr *)&sAddr,0x10);
    if (iVar1 == -1) {
      close(*pSockConnection);
      local_c = -1;
    }
    else {
      local_c = 0;
    }
  }
  return local_c;
}