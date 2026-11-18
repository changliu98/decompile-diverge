int __cdecl func0(int n)
{
  bool v2; // [rsp+1h] [rbp-9h]
  int i; // [rsp+2h] [rbp-8h]

  for ( i = 2; i * i <= n; ++i )
  {
    while ( 1 )
    {
      v2 = 0;
      if ( !(n % i) )
        v2 = n > i;
      if ( !v2 )
        break;
      n /= i;
    }
  }
  return n;
}