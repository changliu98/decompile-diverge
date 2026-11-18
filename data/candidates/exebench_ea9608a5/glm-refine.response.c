void __cdecl dec2bin(int n, char *rbn)
{
  while ( n > 0 )
  {
    *rbn++ = (n & 1) ? '1' : '0';
    n >>= 1;
  }
}