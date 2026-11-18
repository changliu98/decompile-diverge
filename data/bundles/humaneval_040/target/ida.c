bool __cdecl func0(int *l, int size)
{
  int k; // [rsp+0h] [rbp-20h]
  int j; // [rsp+4h] [rbp-1Ch]
  int i; // [rsp+8h] [rbp-18h]

  for ( i = 0; i < size; ++i )
  {
    for ( j = i + 1; j < size; ++j )
    {
      for ( k = j + 1; k < size; ++k )
      {
        if ( !(l[k] + l[j] + l[i]) )
          return 1;
      }
    }
  }
  return 0;
}