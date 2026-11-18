int __cdecl func0(int *arr, int n)
{
  int j; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]
  int inv_count; // [rsp+8h] [rbp-10h]

  inv_count = 0;
  for ( i = 0; i < n; ++i )
  {
    for ( j = i + 1; j < n; ++j )
    {
      if ( arr[i] > arr[j] )
        ++inv_count;
    }
  }
  return inv_count;
}