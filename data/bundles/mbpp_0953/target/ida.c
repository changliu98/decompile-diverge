int __cdecl func0(int *ar, int n)
{
  bool v3; // [rsp+1h] [rbp-25h]
  int temp; // [rsp+2h] [rbp-24h]
  int i_0; // [rsp+6h] [rbp-20h]
  int step; // [rsp+Ah] [rbp-1Ch]
  int count; // [rsp+Eh] [rbp-18h]
  int i; // [rsp+12h] [rbp-14h]
  int res; // [rsp+16h] [rbp-10h]

  res = 0;
  for ( step = 0; step < n - 1; ++step )
  {
    for ( i_0 = 0; i_0 < n - step - 1; ++i_0 )
    {
      if ( ar[i_0] > ar[i_0 + 1] )
      {
        temp = ar[i_0];
        ar[i_0] = ar[i_0 + 1];
        ar[i_0 + 1] = temp;
      }
    }
  }
  for ( i = 0; i < n; ++i )
  {
    for ( count = 1; ; ++count )
    {
      v3 = 0;
      if ( i + 1 < n )
        v3 = ar[i] == ar[i + 1];
      if ( !v3 )
        break;
      ++i;
    }
    if ( res < count )
      res = count;
  }
  return res;
}