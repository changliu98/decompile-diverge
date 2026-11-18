bool __cdecl func0(int *list1, int size1, int *list2, int size2)
{
  int j; // [rsp+0h] [rbp-2Ch]
  bool found; // [rsp+7h] [rbp-25h]
  int i; // [rsp+8h] [rbp-24h]
  char exist; // [rsp+Fh] [rbp-1Dh]

  exist = 1;
  for ( i = 0; i < size2; ++i )
  {
    found = 0;
    for ( j = 0; j < size1; ++j )
    {
      if ( list2[i] == list1[j] )
      {
        found = 1;
        break;
      }
    }
    if ( !found )
      return 0;
  }
  return exist;
}