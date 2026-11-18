int __cdecl func0(int *arr, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int max; // [rsp+4h] [rbp-10h]

  max = -1;
  for ( i = 1; i < size; ++i )
  {
    if ( arr[i] < arr[i - 1] )
      max = i;
  }
  return max;
}