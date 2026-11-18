void __cdecl replaceChar(char *s, char oldc, char newc)
{
  char *sa; // [rsp+4h] [rbp-8h]

  sa = s;
  if ( s )
  {
    while ( *sa )
    {
      if ( *sa == oldc )
        *sa = newc;
      ++sa;
    }
  }
}