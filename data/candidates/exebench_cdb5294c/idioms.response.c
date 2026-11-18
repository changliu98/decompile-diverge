void int2str(int value, int base, char *output)
{
  int i = base;
  while (i)
  {
    *output++ = (value / i % 10) + '0';
    i /= 10;
  }
  *output = '\0';
}