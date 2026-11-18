int __cdecl connectToServer(int *pSockConnection, char *serverIP, int serverPort)
{
  sockaddr_in sAddr;
  int sock;

  // Create a TCP socket (AF_INET = 2, SOCK_STREAM = 1, IPPROTO_IP = 0)
  sock = socket(AF_INET, SOCK_STREAM, 0);
  *pSockConnection = sock;
  
  if (sock == -1)
    return -1;

  // Configure socket address structure
  sAddr.sin_family = AF_INET;
  sAddr.sin_addr.s_addr = inet_addr(serverIP);
  sAddr.sin_port = htons(serverPort);

  // Attempt to connect to the server
  if (connect(sock, (const struct sockaddr *)&sAddr, sizeof(sAddr)) != -1)
    return 0;

  // Connection failed, close the socket and return error
  close(sock);
  return -1;
}