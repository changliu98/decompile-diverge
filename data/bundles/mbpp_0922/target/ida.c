void __cdecl func0(int *arr, int arr_len, int *x, int *y)
{
  int j; // [rsp+0h] [rbp-28h]
  int i; // [rsp+4h] [rbp-24h]

  if ( arr_len >= 2 )
  {
    *x = *arr;
    *y = arr[1];
    for ( i = 0; i < arr_len; ++i )
    {
      for ( j = i + 1; j < arr_len; ++j )
      {
        if ( arr[j] * arr[i] > *y * *x )
        {
          *x = arr[i];
          *y = arr[j];
        }
      }
    }
  }
  else
  {
    *x = 0;
    *y = 0;
  }
}