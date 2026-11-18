int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-Ch]

  if ( !(n % 2) )
    return 2;
  for ( i = 3; i * i <= n; i += 2 )
  {
    if ( !(n % i) )
      return i;
  }
  return n;
}