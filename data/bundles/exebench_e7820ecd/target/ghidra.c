int read_all(int fd,uchar *buf,int count)

{
  int iVar1;
  ssize_t sVar2;
  bool local_21;
  int n;
  int count_local;
  uchar *buf_local;
  int fd_local;
  
  count_local = count;
  buf_local = buf;
  do {
    sVar2 = read(fd,buf_local,(long)count_local);
    iVar1 = (int)sVar2;
    if (0 < iVar1) {
      count_local = count_local - iVar1;
      buf_local = buf_local + iVar1;
    }
    local_21 = 0 < iVar1 && 0 < count_local;
  } while (local_21);
  return iVar1;
}