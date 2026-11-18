int __cdecl func0(int *arr, int n, int k)
{
  int i_0; // [rsp+0h] [rbp-28h]
  int i; // [rsp+4h] [rbp-24h]
  int res; // [rsp+8h] [rbp-20h]
  int max1; // [rsp+Ch] [rbp-1Ch]

  max1 = *arr;
  res = 0;
  for ( i = 1; i < n; ++i )
  {
    if ( arr[i] > max1 )
      max1 = arr[i];
  }
  for ( i_0 = 0; i_0 < n; ++i_0 )
  {
    if ( (max1 - arr[i_0]) % k )
      return -1;
    res += (max1 - arr[i_0]) / k;
  }
  return res;
}