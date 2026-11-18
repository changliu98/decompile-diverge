char *__cdecl my_strupcase(char *str)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; str[i]; ++i )
  {
    if ( str[i] >= 97 && str[i] <= 122 )
      str[i] -= 32;
  }
  return str;
}