int __cdecl connectToServer(int *pSockConnection, char *serverIP, int serverPort)
{
  int v3; // eax
  sockaddr_in sAddr; // [rsp+0h] [rbp-30h] BYREF
  int serverPorta; // [rsp+14h] [rbp-1Ch]
  char *serverIPa; // [rsp+18h] [rbp-18h]
  int *pSockConnectiona; // [rsp+20h] [rbp-10h]

  pSockConnectiona = pSockConnection;
  serverIPa = serverIP;
  serverPorta = serverPort;
  v3 = socket(2, 1, 0);
  *pSockConnection = v3;
  if ( v3 == -1 )
    return -1;
  sAddr.sin_family = 2;
  sAddr.sin_addr.s_addr = inet_addr(serverIPa);
  sAddr.sin_port = htons(serverPorta);
  if ( connect(*pSockConnectiona, (const struct sockaddr *)&sAddr, 0x10u) != -1 )
    return 0;
  close(*pSockConnectiona);
  return -1;
}