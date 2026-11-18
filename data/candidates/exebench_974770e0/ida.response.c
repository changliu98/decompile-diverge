char *__cdecl envstring(char *str)
{
  char *s; // [rsp+0h] [rbp-10h]

  for ( s = str; *s; ++s )
  {
    if ( *s == 45 )
    {
      *s = 95;
    }
    else if ( *s < 97 || *s > 122 )
    {
      if ( *s < 65 || *s > 90 )
      {
        *str = 0;
        return str;
      }
    }
    else
    {
      *s -= 32;
    }
  }
  return str;
}