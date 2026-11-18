int __cdecl bitsToIp4AddrArr(unsigned int ipInt, int *ipArr)
{
  *ipArr = (ipInt & 0xFF000000) >> 24;
  ipArr[1] = (ipInt & 0xFF0000) >> 16;
  ipArr[2] = (unsigned __int16)(ipInt & 0xFF00) >> 8;
  ipArr[3] = (unsigned __int8)ipInt;
  return 0;
}