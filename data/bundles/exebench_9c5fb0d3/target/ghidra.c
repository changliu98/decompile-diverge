int write_data(int fd,uchar *buf,int size)

{
  ssize_t sVar1;
  int ret;
  int cur;
  int size_local;
  uchar *buf_local;
  int fd_local;
  
  cur = 0;
  while( true ) {
    if (cur == size) {
      return 0;
    }
    sVar1 = write(fd,buf + cur,(long)(size - cur));
    if ((int)sVar1 < 1) break;
    cur = (int)sVar1 + cur;
  }
  return -1;
}