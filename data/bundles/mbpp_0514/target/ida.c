int __cdecl func0(int *arr, int len)
{
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < len; ++i )
    sum += arr[i];
  return sum;
}