int bitsToIp4AddrArr(unsigned int time, char *out)
{
  do { (out)[0] = ((time) >> 24) & 0xFF; (out)[1] = ((time) >> 16) & 0xFF; (out)[2] = ((time) >> 8) & 0xFF; (out)[3] = (time) & 0xFF; } while(0);
  return 0;
}