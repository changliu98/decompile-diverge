int __cdecl func0(int *arr, int n)
{
  int i_0; // [rsp+0h] [rbp-24h]
  int left_sum; // [rsp+4h] [rbp-20h]
  int i; // [rsp+8h] [rbp-1Ch]
  int total_sum; // [rsp+Ch] [rbp-18h]

  total_sum = 0;
  for ( i = 0; i < n; ++i )
    total_sum += arr[i];
  left_sum = 0;
  for ( i_0 = 0; i_0 < n; ++i_0 )
  {
    total_sum -= arr[i_0];
    if ( left_sum == total_sum )
      return i_0;
    left_sum += arr[i_0];
  }
  return -1;
}