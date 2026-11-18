void endian_swap32bit(unsigned int *val) {
  unsigned long tmp;
  tmp = *val;
  tmp = (tmp << 24) | ((tmp << 8) & 0x00ff0000) | ((tmp >> 8) & 0x0000ff00) |
        (tmp >> 24);
  *val = tmp;
}