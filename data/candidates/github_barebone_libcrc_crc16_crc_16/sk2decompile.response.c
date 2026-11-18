unsigned short crc_16(unsigned char *data, unsigned long length) {
  unsigned long counter;
  unsigned short crc;
  unsigned char *current;
  if (!(crc_tab16_init & 1)) init_crc16_tab();
  crc = 0x0000;
  current = data;
  if (current != 0) {
    for (counter = 0; counter < length; counter++) {
      crc = (crc >> 8) ^ crc_tab16[(crc ^ (*current++)) & 0x00FF];
    }
  }
  return crc;
}