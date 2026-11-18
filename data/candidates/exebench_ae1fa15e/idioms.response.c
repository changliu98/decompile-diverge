int render_uint32(unsigned int n, char *str)
{
  if (n == 0) {
    str[0] = '0';
    return 1;
  }
  int i = 0;
  while (n > 0) {
    str[i++] = "0123456789abcdef"[n & 0xf];
    n >>= 4;
  }
  return i;
}