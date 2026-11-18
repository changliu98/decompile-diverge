char *__cdecl ft_strrev(char *str)
{
  char c; // [rsp+1h] [rbp-11h]
  int j; // [rsp+2h] [rbp-10h]
  int i; // [rsp+6h] [rbp-Ch]
  int ia; // [rsp+6h] [rbp-Ch]

  i = 0;
  j = 0;
  while ( str[i] )
    ++i;
  for ( ia = i - 1; ia > j; --ia )
  {
    c = str[ia];
    str[ia] = str[j];
    str[j++] = c;
  }
  return str;
}