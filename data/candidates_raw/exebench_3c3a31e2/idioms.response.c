int read_packet(int sock, unsigned char *buf)
{
  return (recv(sock, buf, 1024 - 1, 0));
}