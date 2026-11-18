int medusaReceiveInternal(int sock, unsigned char *buffer, int size) {
  int ret;
  ret = recv(sock, buffer, size, 0);
  return ret;
}