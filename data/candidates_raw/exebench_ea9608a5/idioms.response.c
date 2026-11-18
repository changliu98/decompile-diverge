void int2bin(int i, char *s)
{
  while (i > 0) {
    *s = (i & 1) ? '1' : '0';
    s++;
    i >>= 1;
  }
}