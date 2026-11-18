int __cdecl new_strcpy(char *s, char *t, int num)
{
  bool v4; // [rsp+1h] [rbp-19h]
  int i; // [rsp+2h] [rbp-18h]

  for ( i = 0; ; ++i )
  {
    v4 = 0;
    if ( t[i] )
      v4 = i < num;
    if ( !v4 )
      break;
    s[i] = t[i];
  }
  s[i] = 0;
  return 0;
}