int __cdecl c_strncasecmp(const char *s1, const char *s2, size_t n)
{
  unsigned __int8 c2; // [rsp+Eh] [rbp-32h]
  unsigned __int8 c1; // [rsp+Fh] [rbp-31h]
  const unsigned __int8 *p2; // [rsp+10h] [rbp-30h]
  const unsigned __int8 *p1; // [rsp+18h] [rbp-28h]
  size_t na; // [rsp+20h] [rbp-20h]

  na = n;
  p1 = (const unsigned __int8 *)s1;
  p2 = (const unsigned __int8 *)s2;
  if ( s1 == s2 || !n )
    return 0;
  while ( 1 )
  {
    c1 = c_tolower(*p1);
    c2 = c_tolower(*p2);
    if ( !--na || !c1 || c1 != c2 )
      break;
    ++p1;
    ++p2;
  }
  return c1 - c2;
}