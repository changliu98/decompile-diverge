char *__cdecl trim(char *str, char *trim_chars)
{
  bool v3; // [rsp+Fh] [rbp-21h]
  char *endstr; // [rsp+10h] [rbp-20h]

  if ( !str )
    return 0LL;
  for ( endstr = index(str, 0) - 1; ; --endstr )
  {
    v3 = 0;
    if ( endstr >= str )
      v3 = index(trim_chars, *endstr) != 0LL;
    if ( !v3 )
      break;
    *endstr = 0;
  }
  return str;
}