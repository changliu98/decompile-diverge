void __cdecl dec2bin(int n, char *rbn)
{
  char *v2; // rax

  while ( n > 0 )
  {
    v2 = rbn++;
    if ( (n & 1) != 0 )
      *v2 = 49;
    else
      *v2 = 48;
    n >>= 1;
  }
}