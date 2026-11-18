char *__cdecl substitute(char *string, char chold, char chnew)
{
  char *cp; // [rsp+0h] [rbp-18h]

  cp = string;
  if ( string )
  {
    while ( *cp )
    {
      if ( *cp == chold )
      {
        *cp = chnew;
        return string;
      }
      ++cp;
    }
  }
  return string;
}