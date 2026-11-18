void socket_close_(int *sock) {
  int s = *sock;
  *sock = -1;
  close(s);
}