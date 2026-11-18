char *__cdecl Q_strupr(char *s1)
{
  char *cp; // [rsp+0h] [rbp-10h]

  for ( cp = s1; *cp; ++cp )
  {
    if ( *cp >= 97 && *cp <= 122 )
      *cp -= 32;
  }
  return s1;
}