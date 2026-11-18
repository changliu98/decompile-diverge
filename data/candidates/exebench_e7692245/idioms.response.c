void dwordstore(char *ip, int i)
{
  ip[0] = i & 0xff;
  ip[1] = (i >> 8) & 0xff;
  ip[2] = (i >> 16) & 0xff;
  ip[3] = (i >> 24) & 0xff;
}