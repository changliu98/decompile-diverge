void WordToHex(unsigned int n, char *str)
{
  int i;
  unsigned int m;
  unsigned short t = n;
  for (i = 3; i >= 0; i--) {
    m = t & 0xf;
    if (m < 10)
      str[i] = m + '0';
    else
      str[i] = m + 'A' - 10;
    t = t >> 4;
  }
  str[4] = '\0';
}