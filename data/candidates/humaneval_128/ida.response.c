int __cdecl func0(int *arr, int arr_size)
{
  int i; // [rsp+0h] [rbp-20h]
  int prods; // [rsp+4h] [rbp-1Ch]
  int sum; // [rsp+8h] [rbp-18h]

  if ( !arr_size )
    return -32768;
  sum = 0;
  prods = 1;
  for ( i = 0; i < arr_size; ++i )
  {
    sum += abs(arr[i]);
    if ( !arr[i] )
      prods = 0;
    if ( arr[i] < 0 )
      prods = -prods;
  }
  return prods * sum;
}