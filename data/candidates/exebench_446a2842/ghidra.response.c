int readBytes(int busHandle,int addr,uchar *buf,int len)

{
  int iVar1;
  ssize_t sVar2;
  int n;
  int len_local;
  uchar *buf_local;
  int addr_local;
  int busHandle_local;
  undefined4 local_c;
  
  iVar1 = ioctl(busHandle,0x703,(ulong)(uint)addr);
  if (iVar1 < 0) {
    local_c = -1;
  }
  else {
    sVar2 = read(busHandle,buf,(long)len);
    local_c = (int)sVar2;
  }
  return local_c;
}