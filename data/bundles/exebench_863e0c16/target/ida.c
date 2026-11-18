void __cdecl reverse(char *s)
{
  bool v1; // [rsp+0h] [rbp-12h]
  char tmp; // [rsp+1h] [rbp-11h]
  int j; // [rsp+2h] [rbp-10h]
  int i; // [rsp+6h] [rbp-Ch]
  int ia; // [rsp+6h] [rbp-Ch]

  for ( i = 0; ; ++i )
  {
    v1 = 0;
    if ( s[i] )
      v1 = s[i] != 10;
    if ( !v1 )
      break;
  }
  j = i - 1;
  for ( ia = 0; ia < j; ++ia )
  {
    tmp = s[ia];
    s[ia] = s[j];
    s[j--] = tmp;
  }
}