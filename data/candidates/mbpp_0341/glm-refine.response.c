void __cdecl func0(int *arr, int n, int *result)
{
  qsort(arr, n, sizeof(int), (__compar_fn_t)cmpfunc);
  for (int i = 0; i < n; ++i)
    result[i] = arr[i];
}