int __cdecl func0(char *(*dict)[2], int size)
{
  int j; // [rsp+4h] [rbp-2Ch]
  char *key; // [rsp+8h] [rbp-28h]
  int i; // [rsp+10h] [rbp-20h]
  int has_upper; // [rsp+14h] [rbp-1Ch]
  int has_lower; // [rsp+18h] [rbp-18h]

  if ( !size )
    return 0;
  has_lower = 0;
  has_upper = 0;
  for ( i = 0; i < size; ++i )
  {
    key = (*dict)[2 * i];
    for ( j = 0; key[j]; ++j )
    {
      if ( ((*__ctype_b_loc())[(unsigned __int8)key[j]] & 0x400) == 0 )
        return 0;
      if ( ((*__ctype_b_loc())[(unsigned __int8)key[j]] & 0x100) != 0 )
        has_upper = 1;
      if ( ((*__ctype_b_loc())[(unsigned __int8)key[j]] & 0x200) != 0 )
        has_lower = 1;
      if ( has_lower + has_upper == 2 )
        return 0;
    }
  }
  return 1;
}