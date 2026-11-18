int bitsToIp4AddrArr(unsigned int ipInt, int *ipArr)
{
  ipArr[0] = (ipInt & 0xff000000) >> 24;
  ipArr[1] = (ipInt & 0x00ff0000) >> 16;
  ipArr[2] = (ipInt & 0x0000ff00) >> 8;
  ipArr[3] = (ipInt & 0x000000ff);
  return 0;
}