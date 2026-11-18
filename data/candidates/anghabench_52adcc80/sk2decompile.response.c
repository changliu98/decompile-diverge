unsigned short BigUnsignedShort(unsigned short s) {
  unsigned char b1 = s & 0xff;
  unsigned char b2 = (s >> 8) & 0xff;
  return (b2 << 8) + b1;
}