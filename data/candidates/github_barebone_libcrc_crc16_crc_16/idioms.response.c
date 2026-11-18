unsigned short crc_16(unsigned char *data, long len)
{
  unsigned short crc;
  unsigned char *p;
  long i;
  if ((crc_tab16_init & 1) == 0)
    init_crc16_tab();
  crc = 0;
  p = (unsigned char *)data;
  if (data != ((void *)0))
  {
    for (i = 0; i < len; i++)
    {
      crc = (crc_tab16[(crc ^ *p++) & 0xff] ^ (crc >> 8));
    }
  }
  return (crc);
}