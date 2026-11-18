void __cdecl reverse(char *str)
{
  char c; // [rsp+7h] [rbp-11h]
  int len; // [rsp+8h] [rbp-10h]
  int i; // [rsp+Ch] [rbp-Ch]

  for ( len = 0; str[len]; ++len )
    ;
  for ( i = 0; i < len / 2; ++i )
  {
    c = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = c;
  }
}