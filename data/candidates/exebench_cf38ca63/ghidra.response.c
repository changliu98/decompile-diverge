int bitsToIp4AddrArr(uint ipInt,int *ipArr)

{
  int *ipArr_local;
  uint ipInt_local;
  
  *ipArr = ipInt >> 0x18;
  ipArr[1] = (ipInt & 0xff0000) >> 0x10;
  ipArr[2] = (ipInt & 0xff00) >> 8;
  ipArr[3] = ipInt & 0xff;
  return 0;
}