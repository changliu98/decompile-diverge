unsigned char gfmul(unsigned char a, unsigned char b) {
  unsigned char p = 0;
  while (b) {
    if (b & 1) p ^= a;
    unsigned char c = 0;
    if (a & 0x80) c = 0x1d;
    a = (a << 1) ^ c;
    b >>= 1;
  }
  return p;
}