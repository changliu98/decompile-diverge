int __cdecl func0(int *arr, int n)
{
  int i_1; // [rsp+4h] [rbp-2Ch]
  int j; // [rsp+8h] [rbp-28h]
  int i_0; // [rsp+Ch] [rbp-24h]
  int i; // [rsp+10h] [rbp-20h]
  int max; // [rsp+14h] [rbp-1Ch]
  int *mls; // [rsp+18h] [rbp-18h]

  mls = (int *)malloc(4LL * n);
  max = 0;
  for ( i = 0; i < n; ++i )
    mls[i] = 1;
  for ( i_0 = 0; i_0 < n; ++i_0 )
  {
    for ( j = 0; j < i_0; ++j )
    {
      if ( abs(arr[i_0] - arr[j]) <= 1 && mls[i_0] < mls[j] + 1 )
        mls[i_0] = mls[j] + 1;
    }
  }
  for ( i_1 = 0; i_1 < n; ++i_1 )
  {
    if ( max < mls[i_1] )
      max = mls[i_1];
  }
  free(mls);
  return max;
}