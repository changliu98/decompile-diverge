static unsigned long it_advance(unsigned long it) {
  unsigned long tmp;
  if (it & 0x06000000) {
    tmp = it & 0x06000000;
    tmp <<= 1;
    tmp |= tmp >> 17;
    it &= ~0x06000000;
    it |= tmp;
  } else {
    it &= ~IT_MASK;
  }
  return it;
}