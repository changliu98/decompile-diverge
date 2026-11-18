int __cdecl func0(const char *str)
{
  bool v2; // [rsp+Fh] [rbp-11h]
  int flag_n; // [rsp+10h] [rbp-10h]
  int flag_l; // [rsp+14h] [rbp-Ch]

  flag_l = 0;
  flag_n = 0;
  while ( *str )
  {
    if ( ((*__ctype_b_loc())[*(unsigned __int8 *)str] & 0x400) != 0 )
      flag_l = 1;
    if ( ((*__ctype_b_loc())[*(unsigned __int8 *)str] & 0x800) != 0 )
      flag_n = 1;
    ++str;
  }
  v2 = 0;
  if ( flag_l )
    return flag_n != 0;
  return v2;
}