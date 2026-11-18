void hton16(unsigned short x, void *ptr)
{
  unsigned char *p = (unsigned char *)ptr;
  p[0] = (unsigned char)(x >> 8);
  p[1] = (unsigned char)(x);
}