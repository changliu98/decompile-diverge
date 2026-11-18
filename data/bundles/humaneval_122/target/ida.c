int __cdecl func0(int *arr, int k)
{
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < k; ++i )
  {
    if ( arr[i] >= -99 && arr[i] <= 99 )
      sum += arr[i];
  }
  return sum;
}