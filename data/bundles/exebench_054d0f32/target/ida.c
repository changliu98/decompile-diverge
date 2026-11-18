char *__cdecl my_strupcase(char *str)
{
  int lp; // [rsp+0h] [rbp-14h]

  if ( !str )
    return 0LL;
  for ( lp = 0; str[lp]; ++lp )
  {
    if ( str[lp] >= 97 && str[lp] <= 122 )
      str[lp] -= 32;
  }
  return str;
}