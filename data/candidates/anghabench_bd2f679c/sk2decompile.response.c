void crc8_byte(unsigned char *crc, unsigned char data) {
  int i, mix;
  for (i = 0; i < 8; i++) {
    mix = (*crc ^ data) & 0x01;
    *crc >>= 1;
    data >>= 1;
    if (mix) *crc ^= 0x8C;
  }
  *crc &= 0xFF;
}