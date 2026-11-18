char *__cdecl my_strupcase(char *str)
{
  int lp; // [rsp+0h] [rbp-Ch]

  for ( lp = 0; str[lp]; ++lp )
  {
    if ( str[lp] >= 97 && str[lp] <= 122 )
      str[lp] -= 32;
  }
  return str;
}