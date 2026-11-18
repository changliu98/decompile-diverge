int sendcw(int fd,uchar *buff)

{
  ssize_t sVar1;
  uint *puVar2;
  uchar *buff_local;
  int fd_local;
  uint local_c;
  
  sVar1 = send(fd,buff,0x12,0);
  if (sVar1 == -1) {
    puVar2 = (uint *)__errno_location();
    syslog(3,"ca.so: Send cw failed %d",(ulong)*puVar2);
  }
  local_c = (uint)(sVar1 != -1);
  return local_c;
}