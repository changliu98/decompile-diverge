unsigned short CRC16(unsigned char *data, unsigned long len)
{
  unsigned short crc = 0;
  unsigned char *p = data;
  unsigned char c = 0;
  unsigned char c1 = 0;
  unsigned char c2 = 0;
  if (data == ((void *)0))
    return (0);
  for (len = 0; len < (unsigned long)len; p++)
  {
    c = *p;
    c1 = c & 0xff;
    c2 = c >> 8;
    if ((crc & 0x8000) == 0x8000)
      crc = (crc << 1) ^ 0x8005;
    else
      crc = (crc << 1);
    crc = (crc ^ c1);
    c = c2;
    c1 = c & 0xff;
    c2 = c >> 8;
    if ((crc & 0x8000) == 0x8000)
      crc = (crc << 1) ^ 0x8005;
    else
      crc = (crc << 1);
    crc = (crc ^ c1);
  }
  return (crc);
}