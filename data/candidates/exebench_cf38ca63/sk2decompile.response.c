int bitsToIp4AddrArr(unsigned int bits, unsigned char *ip4AddrArr) {
  ip4AddrArr[0] = (bits & 0xff000000) >> 24;
  ip4AddrArr[1] = (bits & 0x00ff0000) >> 16;
  ip4AddrArr[2] = (bits & 0x0000ff00) >> 8;
  ip4AddrArr[3] = (bits & 0x000000ff);
  return 0;
}