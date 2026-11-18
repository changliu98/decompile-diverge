void __cdecl func0(int *arr, int arr_size, int k, int *out)
{
  int i_0; // [rsp+0h] [rbp-28h]
  int temp; // [rsp+4h] [rbp-24h]
  int j; // [rsp+8h] [rbp-20h]
  int i; // [rsp+Ch] [rbp-1Ch]

  for ( i = 0; i < arr_size - 1; ++i )
  {
    for ( j = 0; j < arr_size - i - 1; ++j )
    {
      if ( arr[j] > arr[j + 1] )
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  for ( i_0 = 0; i_0 < k; ++i_0 )
    out[i_0] = arr[i_0 + arr_size - k];
}