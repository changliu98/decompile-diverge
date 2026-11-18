void __cdecl strcpy2(char *s, char *t)
{
  char v2; // al

  while ( 1 )
  {
    v2 = *t;
    *s = *t;
    if ( !v2 )
      break;
    ++s;
    ++t;
  }
}