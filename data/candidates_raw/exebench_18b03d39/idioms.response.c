static void bswap32(void *in)
{
  int i = *(int *)in;
  int j = (i>>24)&0xff;
  j |= (i>>16)&0xff00;
  j |= (i>>8)&0xff0000;
  j |= (i>>0)&0xff000000;
  *(int *)in = j;
}