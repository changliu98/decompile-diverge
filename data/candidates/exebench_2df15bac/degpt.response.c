int force_write(int fd,uchar *buf,int sz)

{
  int iVar1;
  ssize_t sVar2;
  int rd;
  int got;
  int sz_local;
  uchar *buf_local;
  int fd_local;
  
  got = 0;
  sz_local = sz;
  buf_local = buf;
  while( true ) {
    if (sz_local < 1) {
      return got;
    }
    sVar2 = write(fd,buf_local,(long)sz_local);
    iVar1 = (int)sVar2;
    if (iVar1 < 1) break;
    got = iVar1 + got;
    buf_local = buf_local + iVar1;
    sz_local = sz_local - iVar1;
  }
  return got;
}