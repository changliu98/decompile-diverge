unsigned char _count_bits(unsigned int x) {
  x = (x & 0x5555) + ((x >> 1) & 0x5555);
  x = (x & 0x3333) + ((x >> 2) & 0x3333);
  x = (x & 0x0f0f) + ((x >> 4) & 0x0f0f);
  x = (x & 0x00ff) + ((x >> 8) & 0x00ff);
  return x;
}