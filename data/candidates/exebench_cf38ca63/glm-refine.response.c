int __cdecl bitsToIp4AddrArr(unsigned int ipInt, int *ipArr)
{
  ipArr[0] = (ipInt >> 24) & 0xFF;
  ipArr[1] = (ipInt >> 16) & 0xFF;
  ipArr[2] = (ipInt >> 8)  & 0xFF;
  ipArr[3] = ipInt         & 0xFF;
  return 0;
}