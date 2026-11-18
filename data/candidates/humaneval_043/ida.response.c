bool __cdecl func0(int *l, int size)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]

  for ( i = 0; i < size; ++i )
  {
    for ( j = i + 1; j < size; ++j )
    {
      if ( !(l[j] + l[i]) )
        return 1;
    }
  }
  return 0;
}