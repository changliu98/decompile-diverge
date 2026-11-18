int __cdecl func0(int *arr, int *dep, int n)
{
  bool v4; // [rsp+Bh] [rbp-25h]
  int j; // [rsp+Ch] [rbp-24h]
  int i; // [rsp+10h] [rbp-20h]
  int result; // [rsp+14h] [rbp-1Ch]
  int plat_needed; // [rsp+18h] [rbp-18h]

  qsort(arr, n, 4uLL, (__compar_fn_t)compare);
  qsort(dep, n, 4uLL, (__compar_fn_t)compare);
  plat_needed = 1;
  result = 1;
  i = 1;
  j = 0;
  while ( 1 )
  {
    v4 = 0;
    if ( i < n )
      v4 = j < n;
    if ( !v4 )
      break;
    if ( arr[i] > dep[j] )
    {
      --plat_needed;
      ++j;
    }
    else
    {
      ++plat_needed;
      ++i;
      if ( plat_needed > result )
        result = plat_needed;
    }
  }
  return result;
}