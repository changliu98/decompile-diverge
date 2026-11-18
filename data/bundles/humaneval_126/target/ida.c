bool __cdecl func0(const int *lst, int lst_size)
{
  int i; // [rsp+0h] [rbp-18h]

  if ( !lst_size )
    return 1;
  for ( i = 1; i < lst_size; ++i )
  {
    if ( lst[i] < lst[i - 1] )
      return 0;
    if ( i >= 2 && lst[i] == lst[i - 1] && lst[i] == lst[i - 2] )
      return 0;
  }
  return 1;
}