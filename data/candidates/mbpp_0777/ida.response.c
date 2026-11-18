int __cdecl func0(int *arr, int n)
{
  int i; // [rsp+Ch] [rbp-14h]
  int sum; // [rsp+10h] [rbp-10h]

  qsort(arr, n, 4uLL, (__compar_fn_t)compare);
  sum = *arr;
  for ( i = 0; i < n - 1; ++i )
  {
    if ( arr[i] != arr[i + 1] )
      sum += arr[i + 1];
  }
  return sum;
}