void __cdecl reverse(char *s)
{
  int v1; // ecx
  int len; // [rsp+4h] [rbp-14h]
  int i; // [rsp+8h] [rbp-10h]
  int ia; // [rsp+8h] [rbp-10h]
  char c; // [rsp+Fh] [rbp-9h]

  i = 0;
  for ( len = 0; ; ++len )
  {
    v1 = i++;
    if ( !s[v1] )
      break;
  }
  for ( ia = 0; ia < len / 2; ++ia )
  {
    c = s[ia];
    s[ia] = s[len - 1 - ia];
    s[len - 1 - ia] = c;
  }
}