int write_buff(int fd,uchar *data,ssize_t size)

{
  ssize_t sVar1;
  ssize_t sz;
  ssize_t n;
  char *ptr;
  ssize_t size_local;
  uchar *data_local;
  int fd_local;
  
  sz = size;
  ptr = (char *)data;
  while( true ) {
    if (sz < 1) {
      return (int)size;
    }
    sVar1 = write(fd,ptr,sz);
    if (sVar1 < 0) break;
    sz = sz - sVar1;
    ptr = ptr + sVar1;
  }
  return -1;
}