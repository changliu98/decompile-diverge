bool __cdecl func0(int *dict, int size, int n)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < size; ++i )
  {
    if ( dict[i] != n )
      return 0;
  }
  return 1;
}