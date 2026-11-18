int __cdecl func0(int *coins, int m, int V)
{
  int sub_res; // [rsp+Ch] [rbp-24h]
  int i; // [rsp+10h] [rbp-20h]
  int res; // [rsp+14h] [rbp-1Ch]

  if ( !V )
    return 0;
  res = 0x7FFFFFFF;
  for ( i = 0; i < m; ++i )
  {
    if ( coins[i] <= V )
    {
      sub_res = func0(coins, m, V - coins[i]);
      if ( sub_res != 0x7FFFFFFF && sub_res + 1 < res )
        res = sub_res + 1;
    }
  }
  return res;
}