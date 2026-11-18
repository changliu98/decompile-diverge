const char *__cdecl convert_set_base(const char *s, int *base)
{
  const char *sa; // [rsp+8h] [rbp-8h]

  sa = s;
  *base = 10;
  if ( s )
  {
    if ( *s == 48 )
    {
      sa = s + 1;
      if ( s[1] == 120 || *sa == 88 )
      {
        *base = 16;
        return s + 2;
      }
    }
  }
  return sa;
}