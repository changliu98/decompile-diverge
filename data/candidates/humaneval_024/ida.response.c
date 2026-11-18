int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 2; i * i <= n; ++i )
  {
    if ( !(n % i) )
      return n / i;
  }
  return 1;
}