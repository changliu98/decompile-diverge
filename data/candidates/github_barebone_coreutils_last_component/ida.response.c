char *__cdecl last_component(const char *name)
{
  const char *p; // [rsp+0h] [rbp-20h]
  bool last_was_slash; // [rsp+Fh] [rbp-11h]

  while ( *name == 47 )
    ++name;
  last_was_slash = 0;
  for ( p = name; *p; ++p )
  {
    if ( *p == 47 )
    {
      last_was_slash = 1;
    }
    else if ( last_was_slash )
    {
      name = p;
      last_was_slash = 0;
    }
  }
  return (char *)name;
}