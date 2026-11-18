int *__cdecl func0(int *arr, int length, int *output)
{
  int i; // [rsp+0h] [rbp-2Ch]
  int index; // [rsp+4h] [rbp-28h]
  int smallestEven; // [rsp+8h] [rbp-24h]

  smallestEven = 0x7FFFFFFF;
  index = -1;
  for ( i = 0; i < length; ++i )
  {
    if ( !(arr[i] % 2) && (arr[i] < smallestEven || index == -1) )
    {
      smallestEven = arr[i];
      index = i;
    }
  }
  if ( index == -1 )
    return 0LL;
  *output = smallestEven;
  output[1] = index;
  return output;
}