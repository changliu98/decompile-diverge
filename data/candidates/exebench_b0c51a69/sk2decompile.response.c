int connectToServer(int *sock, char *ip, int port) {
  struct sockaddr_in server;
  *sock = socket(2, 1, 0);
  if (*sock == -1) return -1;
  server.sin_family = 2;
  server.sin_addr.s_addr = inet_addr(ip);
  server.sin_port = htons(port);
  if (connect(*sock, (struct sockaddr *)&server, 16) == -1) {
    close(*sock);
    return -1;
  }
  return 0;
}