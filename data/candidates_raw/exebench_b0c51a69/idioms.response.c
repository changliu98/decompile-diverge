int connectToServer(int *socketConnection, char *serverIP, int serverPort){
  struct sockaddr_in serverAddress;
  if(( *socketConnection = socket(2, SOCK_STREAM, 0)) == -1){
    return -1;
  }
  serverAddress.sin_family = 2;
  serverAddress.sin_addr.s_addr = inet_addr(serverIP);
  serverAddress.sin_port = htons(serverPort);
  if(connect(*socketConnection, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1){
    close(*socketConnection);
    return -1;
  }
  return 0;
}