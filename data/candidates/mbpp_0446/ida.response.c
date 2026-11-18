int __cdecl func0(const int *tup, int tup_size, const int *lst, int lst_size)
{
  int j; // [rsp+0h] [rbp-28h]
  int i; // [rsp+4h] [rbp-24h]
  int count; // [rsp+8h] [rbp-20h]

  count = 0;
  for ( i = 0; i < tup_size; ++i )
  {
    for ( j = 0; j < lst_size; ++j )
    {
      if ( tup[i] == lst[j] )
      {
        ++count;
        break;
      }
    }
  }
  return count;
}