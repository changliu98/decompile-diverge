void __cdecl func0(int *arr, int n, int *result)
{
  int i; // [rsp+4h] [rbp-1Ch]

  qsort(arr, n, 4uLL, (__compar_fn_t)cmpfunc);
  for ( i = 0; i < n; ++i )
    result[i] = arr[i];
}