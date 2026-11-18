const char *__cdecl convert_set_sign(const char *s, int *sign)
{
  const char *sa; // [rsp+8h] [rbp-8h]

  sa = s;
  *sign = 1;
  if ( s )
  {
    if ( *s == 43 )
    {
      *sign = 1;
      return s + 1;
    }
    else if ( *s == 45 )
    {
      *sign = -1;
      return s + 1;
    }
  }
  return sa;
}