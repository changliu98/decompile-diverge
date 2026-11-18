void byte2bits(int i, char *s)
{
  int j = 8 - 1;
  while (j >= 0)
    *s++ = (i >> j--) & 1 + '0';
  *s = '\0';
}