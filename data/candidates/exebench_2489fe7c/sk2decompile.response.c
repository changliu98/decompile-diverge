void crc16_b(unsigned int *crc, unsigned char b) {
  int i;
  for (i = 0; i < 8; i++) {
    *crc <<= 1;
    if ((b ^ (*crc >> 16)) & 1) *crc ^= 0x8005;
    b >>= 1;
  }
  *crc &= 0xffff;
}