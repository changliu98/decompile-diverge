unsigned char fdc_crc4(unsigned char *buf, unsigned long len) {
  unsigned long i;
  unsigned char crc = 0x0f;
  for (i = 0; i < len; i++) {
    crc ^= *buf++;
  }
  return crc;
}