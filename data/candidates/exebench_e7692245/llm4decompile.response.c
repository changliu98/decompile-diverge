void dwordstore(unsigned char *x,u32 i)
{
  x[0]=i&0xff;
  x[1]=(i>>8)&0xff;
  x[2]=(i>>16)&0xff;
  x[3]=(i>>24)&0xff;
}