unsigned int swizzle(unsigned int x, unsigned int mask) {
  unsigned int result = 0;
  while (mask) {
    result = (result << 1) | (x & 1);
    x >>= 1;
    mask >>= 1;
  }
  return result;
}