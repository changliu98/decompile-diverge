int write_sock(int sockhandle,uchar *buf,int length)

{
  ssize_t sVar1;
  int byte_send;
  int length_local;
  uchar *buf_local;
  int sockhandle_local;
  
  sVar1 = write(sockhandle,buf,(ulong)(uint)length);
  return length - (int)sVar1;
}