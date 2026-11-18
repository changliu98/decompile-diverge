int write_bus(int busfd,uchar *buf,int bufsize)

{
  ssize_t sVar1;
  int bufsize_local;
  uchar *buf_local;
  int busfd_local;
  
  sVar1 = write(busfd,buf,(long)bufsize);
  return (int)sVar1;
}