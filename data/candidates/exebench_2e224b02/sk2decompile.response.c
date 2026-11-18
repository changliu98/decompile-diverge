void prtl16(long n, char *s) {
  char buf[9];
  int i;
  buf[0] = 0;
  for (i = 1; i < 9; i++) {
    buf[i] = "0123456789ABCDEF"[n & 0x0F];
    n >>= 4;
  }
  for (i = 8; buf[i] == '0'; i--)
    ;
  if (i == 0) i = 1;
  while (i >= 0) *s++ = buf[i--];
}