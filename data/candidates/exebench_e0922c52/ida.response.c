void __cdecl outfname(char *s)
{
  while ( *s )
    ++s;
  *(s - 1) = 115;
}