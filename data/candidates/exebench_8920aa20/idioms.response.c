int medusaReceiveInternal(int socket, char *buf, int length)
{
  return recv(socket, buf, length, 0);
}