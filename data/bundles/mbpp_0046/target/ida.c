bool __cdecl func0(int *data, int length)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]

  for ( i = 0; i < length; ++i )
  {
    for ( j = i + 1; j < length; ++j )
    {
      if ( data[i] == data[j] )
        return 0;
    }
  }
  return 1;
}