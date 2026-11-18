const char *__cdecl func0(int *lst1, int size1, int *lst2, int size2)
{
  int i_0; // [rsp+0h] [rbp-30h]
  int i; // [rsp+4h] [rbp-2Ch]
  int num; // [rsp+8h] [rbp-28h]

  num = 0;
  for ( i = 0; i < size1; ++i )
  {
    if ( !(lst1[i] % 2) )
      ++num;
  }
  for ( i_0 = 0; i_0 < size2; ++i_0 )
  {
    if ( !(lst2[i_0] % 2) )
      ++num;
  }
  if ( num < size1 )
    return (const char *)&unk_2008;
  else
    return (const char *)&unk_2004;
}