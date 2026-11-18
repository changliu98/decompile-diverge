void itoa(int value, int base, char *output)
{
  while (base)
  {
    *output++ = (value / base % 10) + '0';
    base /= 10;
  }
}