int medusaReceiveInternal(int socket,uchar *buf,int length)

{
  ssize_t sVar1;
  int length_local;
  uchar *buf_local;
  int socket_local;
  
  sVar1 = recv(socket,buf,(ulong)(uint)length,0);
  return (int)sVar1;
}