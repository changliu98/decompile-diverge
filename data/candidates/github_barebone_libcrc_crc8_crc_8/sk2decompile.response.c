unsigned char crc_8(unsigned char *message, unsigned long length) {
  unsigned char crc = 0;
  unsigned char *p = message;
  unsigned long counter;
  if (message != NULL) {
    for (counter = 0; counter < length; counter++) {
      crc = crc_8_table[crc ^ *p++];
    }
  }
  return crc;
}