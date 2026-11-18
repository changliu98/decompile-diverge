int __cdecl func0(int x, int y)
{
  int k; // [rsp+0h] [rbp-14h]
  int gcd; // [rsp+4h] [rbp-10h]

  gcd = 1;
  if ( !(x % y) )
    return y;
  for ( k = y / 2; k > 0; --k )
  {
    if ( !(x % k) && !(y % k) )
      return k;
  }
  return gcd;
}