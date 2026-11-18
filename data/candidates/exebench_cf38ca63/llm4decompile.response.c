int bitsToIp4AddrArr(uint32_t ipInt, uint8_t *ipArr)
{
 ipArr[0] = (ipInt >> 24) & 0xff;
 ipArr[1] = (ipInt >> 16) & 0xff;
 ipArr[2] = (ipInt >> 8) & 0xff;
 ipArr[3] = ipInt & 0xff;
 return 0;
}