void dec2bin(int n, char *s) {
  while (n > 0) {
    if (n & 1)
      *s++ = '1';
    else
      *s++ = '0';
    n >>= 1;
  }
}