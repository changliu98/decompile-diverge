int wfaCtrlRecv(int sock,uchar *buf)

{
  ssize_t sVar1;
  int bytesRecvd;
  uchar *buf_local;
  int sock_local;
  
  sVar1 = recv(sock,buf,0x3ff,0);
  return (int)sVar1;
}