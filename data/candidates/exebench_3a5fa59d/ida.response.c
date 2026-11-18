char *__cdecl strichr(char *p, int c)
{
  char *t; // [rsp+0h] [rbp-18h]

  if ( p )
  {
    for ( t = p; *t; ++t )
      ;
    while ( t >= p )
    {
      t[1] = *t;
      --t;
    }
    *p = c;
  }
  return p;
}