bool __cdecl func0(int *test_list, int length)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int i; // [rsp+4h] [rbp-18h]

  for ( i = 0; i < length - 1; ++i )
  {
    for ( j = i + 1; j < length; ++j )
    {
      if ( test_list[i] == test_list[j] )
        return 0;
    }
  }
  return 1;
}