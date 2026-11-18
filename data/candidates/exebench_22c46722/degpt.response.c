int read_sock(int sockhandle,uchar *buf,int length)

{
  int iVar1;
  ssize_t sVar2;
  int i;
  int mlength;
  uchar *ptbuf;
  int byte_read;
  int length_local;
  uchar *buf_local;
  int sockhandle_local;
  
  i = 0;
  mlength = length;
  ptbuf = buf;
  while( true ) {
    sVar2 = read(sockhandle,ptbuf,(ulong)(uint)mlength);
    iVar1 = (int)sVar2;
    if (0 < iVar1) {
      ptbuf = ptbuf + iVar1;
      mlength = mlength - iVar1;
    }
    i = i + 1;
    if (10000 < i) break;
    if (mlength < 1) {
      return mlength;
    }
  }
  return -1;
}