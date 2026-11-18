int __cdecl next_arr_seq(int *arr, int len, int maxval)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < len; ++i )
  {
    if ( ++arr[i] <= maxval )
      return 1;
    arr[i] = 0;
  }
  return 0;
}