int __cdecl func0(int *arr, int arr_size)
{
  int j; // [rsp+0h] [rbp-20h]
  int count; // [rsp+4h] [rbp-1Ch]
  int i; // [rsp+8h] [rbp-18h]

  for ( i = 0; i < arr_size; ++i )
  {
    count = 0;
    for ( j = 0; j < arr_size; ++j )
    {
      if ( arr[i] == arr[j] )
        ++count;
    }
    if ( count % 2 )
      return arr[i];
  }
  return -1;
}