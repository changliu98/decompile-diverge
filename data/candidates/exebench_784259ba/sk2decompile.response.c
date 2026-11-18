int inet_close(int *sock) {
  close(*sock);
  *sock = 0;
  return 0;
}