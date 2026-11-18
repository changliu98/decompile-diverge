int __cdecl medusaReceiveInternal(int socket, unsigned __int8 *buf, int length)
{
  return recv(socket, buf, (unsigned int)length, 0);
}