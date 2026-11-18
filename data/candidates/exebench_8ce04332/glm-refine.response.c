void __cdecl int2str(int value, int divisor, char *output)
{
  while (divisor)
  {
    *output++ = (value / divisor % 10) + '0';
    divisor /= 10;
  }
}