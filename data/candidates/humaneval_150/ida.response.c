int __cdecl func0(int n, int x, int y)
{
  int i; // [rsp+0h] [rbp-18h]
  int isp; // [rsp+4h] [rbp-14h]

  isp = n >= 2;
  for ( i = 2; i * i <= n; ++i )
  {
    if ( !(n % i) )
      isp = 0;
  }
  if ( !isp )
    return y;
  return x;
}