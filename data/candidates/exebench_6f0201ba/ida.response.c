void __cdecl reverse(char *str)
{
  char tmp; // [rsp+7h] [rbp-11h]
  int i; // [rsp+8h] [rbp-10h]
  int length; // [rsp+Ch] [rbp-Ch]

  for ( length = 0; str[length]; ++length )
    ;
  for ( i = 0; i < length / 2; ++i )
  {
    tmp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = tmp;
  }
}