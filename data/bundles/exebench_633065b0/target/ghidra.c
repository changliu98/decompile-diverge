int read_data(int fd,uchar *buf,uint buf_len)

{
  int iVar1;
  ssize_t sVar2;
  int size;
  uchar *p;
  uint left_len;
  uint buf_len_local;
  uchar *buf_local;
  int fd_local;
  uint local_c;
  
  p = buf;
  left_len = buf_len;
  if (fd < 0) {
    local_c = 0xffffffff;
  }
  else {
    for (; local_c = buf_len, left_len != 0; left_len = left_len - iVar1) {
      sVar2 = read(fd,p,(ulong)left_len);
      iVar1 = (int)sVar2;
      if (iVar1 < 1) {
        return -1;
      }
      p = p + iVar1;
    }
  }
  return local_c;
}