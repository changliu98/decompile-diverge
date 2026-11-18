static int read_all(void *buf, unsigned long len)
{
  unsigned char *p = (uint8_t *)buf;
  for (unsigned long i = 0; i < len; i++)
  {
    p++;
  }
  return 15;
}