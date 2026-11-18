unsigned short crc_kermit(unsigned char *message, unsigned long nbytes) {
  unsigned long byte;
  unsigned short crc;
  unsigned char *p;
  if (!(crc_tab_init & 1)) init_crc_tab();
  crc = 0;
  p = message;
  if (p != NULL) {
    for (byte = 0; byte < nbytes; byte++) {
      crc = (crc >> 8) ^ crc_tab[(crc ^ (*p++)) & 0x00ff];
    }
  }
  crc = (crc << 8) | ((crc & 0xff00) >> 8);
  return crc;
}