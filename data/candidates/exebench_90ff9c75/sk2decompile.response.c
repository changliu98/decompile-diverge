void WordToHex(unsigned int word, char *hex) {
  unsigned short w;
  int i;
  w = word;
  for (i = 3; i >= 0; i--) {
    int n = w & 0x0F;
    if (n < 10)
      hex[i] = n + '0';
    else
      hex[i] = n - 10 + 'A';
    w >>= 4;
  }
  hex[4] = 0;
}