int __cdecl func0(int *arr, int arr_size, int x)
{
  int i; // [rsp+0h] [rbp-18h]
  int count; // [rsp+4h] [rbp-14h]

  count = 0;
  for ( i = 0; i < arr_size; ++i )
  {
    if ( arr[i] == x )
      ++count;
  }
  return count;
}