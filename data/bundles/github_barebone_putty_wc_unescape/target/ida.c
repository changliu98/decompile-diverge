bool __cdecl wc_unescape(char *output, const char *wildcard)
{
  char *v2; // rax
  char *v3; // rax

  while ( *wildcard )
  {
    if ( *wildcard == 92 )
    {
      if ( *++wildcard )
      {
        if ( output )
        {
          v2 = output++;
          *v2 = *wildcard;
        }
        ++wildcard;
      }
    }
    else
    {
      if ( *wildcard == 42 || *wildcard == 63 || *wildcard == 91 || *wildcard == 93 )
        return 0;
      if ( output )
      {
        v3 = output++;
        *v3 = *wildcard;
      }
      ++wildcard;
    }
  }
  if ( output )
    *output = 0;
  return 1;
}