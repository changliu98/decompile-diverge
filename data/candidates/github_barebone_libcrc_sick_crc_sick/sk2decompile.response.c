unsigned short crc_sick(unsigned char *data, unsigned long length) {
  unsigned long i;
  unsigned short crc;
  unsigned short high;
  unsigned short low;
  unsigned char *p;
  crc = 0;
  p = data;
  high = 0;
  if (data != NULL) {
    for (i = 0; i < length; i++) {
      low = *p;
      if (crc & 0x8000)
        crc = (crc << 1) ^ 0x8005;
      else
        crc = (crc << 1);
      crc = crc ^ (high | low);
      high = low << 8;
      p++;
    }
  }
  crc = (crc & 0xff) << 8 | (crc & 0xff00) >> 8;
  return crc;
}