bool __cdecl func0(int *arr, int size)
{
  int i; // [rsp+0h] [rbp-1Ch]
  int num; // [rsp+4h] [rbp-18h]

  num = 0;
  if ( size )
  {
    for ( i = 1; i < size; ++i )
    {
      if ( arr[i] < arr[i - 1] )
        ++num;
    }
    if ( arr[size - 1] > *arr )
      ++num;
    return num < 2;
  }
  else
  {
    return 1;
  }
}