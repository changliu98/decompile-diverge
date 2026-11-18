void __cdecl trim(char *str)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; str[i]; ++i )
    ;
  str[i - 1] = 0;
}