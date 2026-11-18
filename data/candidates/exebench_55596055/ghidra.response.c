void clean_fd(int sock,int *cache_sock,int *nsock)

{
  int i;
  int *nsock_local;
  int *cache_sock_local;
  int sock_local;
  
  for (i = 0; i < 2; i = i + 1) {
    if (cache_sock[i] == sock) {
      cache_sock[i] = 0;
    }
  }
  close(sock);
  *nsock = *nsock + -1;
  return;
}