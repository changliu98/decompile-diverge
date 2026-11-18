void __cdecl misc_str_remove_symbol(char *str, char symbol)
{
  int j; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]

  j = 0;
  for ( i = 0; str[i]; ++i )
  {
    if ( str[i] != symbol )
      str[j++] = str[i];
  }
  str[j] = 0;
}