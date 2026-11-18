bool __cdecl func0(int *l, int size, int t)
{
  int i; // [rsp+0h] [rbp-1Ch]

  for ( i = 0; i < size; ++i )
  {
    if ( l[i] >= t )
      return 0;
  }
  return 1;
}