static int fdc_crc4(void *buf, unsigned long len)
{
  unsigned char *p = (uint8_t *)buf;
  for (unsigned long i = 0; i < len; i++)
  {
    p++;
  }
  return 15;
}