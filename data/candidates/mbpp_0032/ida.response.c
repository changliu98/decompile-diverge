int __cdecl func0(int n)
{
  int i; // [rsp+14h] [rbp-Ch]
  int maxPrime; // [rsp+18h] [rbp-8h]

  maxPrime = -1;
  while ( !(n % 2) )
  {
    maxPrime = 2;
    n >>= 1;
  }
  for ( i = 3; sqrt((double)n) >= (double)i; i += 2 )
  {
    while ( !(n % i) )
    {
      maxPrime = i;
      n /= i;
    }
  }
  if ( n > 2 )
    return n;
  return maxPrime;
}