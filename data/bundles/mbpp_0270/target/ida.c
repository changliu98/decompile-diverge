int __cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-14h]
  int sum; // [rsp+4h] [rbp-10h]

  sum = 0;
  for ( i = 0; i < n; i += 2 )
  {
    if ( !(arr[i] % 2) )
      sum += arr[i];
  }
  return sum;
}