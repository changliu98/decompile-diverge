int __cdecl func0(int *arr, int n, int k)
{
  int v4; // [rsp+0h] [rbp-20h]
  int j; // [rsp+4h] [rbp-1Ch]
  int i; // [rsp+8h] [rbp-18h]
  int ans; // [rsp+Ch] [rbp-14h]

  ans = n - 1;
  qsort(arr, n, 4uLL, (__compar_fn_t)&strcmp);
  for ( i = 0; i < n; ++i )
  {
    j = find_ind(arr[i], i, n, k, arr);
    if ( j != -1 )
    {
      if ( ans >= n - (j - i + 1) )
        v4 = n - (j - i + 1);
      else
        v4 = ans;
      ans = v4;
    }
  }
  return ans;
}