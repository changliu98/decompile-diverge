char *__cdecl stringCopy(char *s, const char *t)
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
  return s;
}