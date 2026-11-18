int __cdecl func0(int *arr, int size)
{
  int i; // [rsp+4h] [rbp-14h]
  int out; // [rsp+8h] [rbp-10h]

  out = 0;
  for ( i = 0; i < size / 2; ++i )
  {
    if ( arr[i] != arr[size - 1 - i] )
      ++out;
  }
  return out;
}