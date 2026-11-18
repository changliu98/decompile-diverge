int __cdecl func0(int n, int x, int y)
{
  int k; // [rsp+4h] [rbp-14h]
  int ans; // [rsp+8h] [rbp-10h]

  ans = 0x80000000;
  for ( k = 0; k <= n; ++k )
  {
    if ( k % x == y && ans < k )
      ans = k;
  }
  if ( ans < 0 || ans > n )
    return -1;
  else
    return ans;
}