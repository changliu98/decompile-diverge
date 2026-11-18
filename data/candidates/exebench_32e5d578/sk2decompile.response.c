void intToBin(unsigned int n, int *bin) {
  int i;
  for (i = 0; i < 8; i++) {
    bin[i] = (n & 0x80) ? 1 : 0;
    n <<= 1;
  }
}