int __cdecl func0(int *xs, int size)
{
  int i; // [rsp+0h] [rbp-14h]
  int min_val; // [rsp+4h] [rbp-10h]

  min_val = 0x7FFFFFFF;
  for ( i = 0; i < size; ++i )
  {
    if ( xs[i] < min_val )
      min_val = xs[i];
  }
  return min_val;
}