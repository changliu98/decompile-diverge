int __cdecl c_strcasecmp(const char *s1, const char *s2)
{
  unsigned __int8 c2; // [rsp+6h] [rbp-2Ah]
  unsigned __int8 c1; // [rsp+7h] [rbp-29h]
  const unsigned __int8 *p2; // [rsp+8h] [rbp-28h]
  const unsigned __int8 *p1; // [rsp+10h] [rbp-20h]

  p1 = (const unsigned __int8 *)s1;
  p2 = (const unsigned __int8 *)s2;
  if ( s1 == s2 )
    return 0;
  while ( 1 )
  {
    c1 = c_tolower(*p1);
    c2 = c_tolower(*p2);
    if ( !c1 || c1 != c2 )
      break;
    ++p1;
    ++p2;
  }
  return c1 - c2;
}