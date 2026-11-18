char *__cdecl mystpcpy(char *to, const char *from)
{
  char v2; // al

  while ( 1 )
  {
    v2 = *from;
    *to = *from;
    if ( !v2 )
      break;
    ++from;
    ++to;
  }
  return to;
}