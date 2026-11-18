int __cdecl func0(const char *s)
{
  bool v2; // [rsp+17h] [rbp-19h]
  int i; // [rsp+18h] [rbp-18h]
  int count; // [rsp+1Ch] [rbp-14h]

  count = 0;
  for ( i = 0; ; ++i )
  {
    v2 = 0;
    if ( s[i] )
      v2 = 2 * i < strlen(s);
    if ( !v2 )
      break;
    if ( strchr("AEIOU", s[2 * i]) )
      ++count;
  }
  return count;
}