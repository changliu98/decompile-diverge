void endian_swap16bit(unsigned short *value) {
  unsigned short temp;
  temp = *value;
  temp = (temp >> 8) | (temp << 8);
  *value = temp;
}