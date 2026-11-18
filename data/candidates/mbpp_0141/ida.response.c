void __cdecl func0(int *arr, int n)
{
  int max_idx; // [rsp+Ch] [rbp-14h]

  while ( n > 1 )
  {
    max_idx = find_max_index(arr, n);
    if ( max_idx != n - 1 )
    {
      reverse(arr, 0, max_idx);
      reverse(arr, 0, n - 1);
    }
    --n;
  }
}