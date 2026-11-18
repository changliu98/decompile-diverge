void itohex(long n, char *s)
{
  int i;
  char buf[9];
  char *t = s;
  buf[0] = '\0';
  for (i = 1; i < 9; i++) {
    buf[i] = "0123456789abcdef"[n & 0xf];
    n >>= 4;
  }
  for (i = 8; buf[i] == '0'; i--)
    ;
  if (i == 0)
    i = 1;
  while (i >= 0)
    *t++ = buf[i--];
}