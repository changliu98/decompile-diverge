char *itoa(unsigned int n, char *s)
{
  char *tb = "0123456789ABCDEF";
  char *ts = s;
  char *ds = s;
  *ts++ = '\0';
  while (n) {
    *ts++ = tb[n & 0xf];
    n >>= 4;
  }
  if (!*ts)
    *ts++ = '0';
  do
    *ds++ = *ts--;
  while (*ts);
  return s;
}