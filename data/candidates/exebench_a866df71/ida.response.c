char *__cdecl skip(char *s, char c)
{
  char *v2; // rax
  bool v4; // [rsp+0h] [rbp-Ah]

  while ( 1 )
  {
    v4 = 0;
    if ( *s != c )
      v4 = *s != 0;
    if ( !v4 )
      break;
    ++s;
  }
  if ( *s )
  {
    v2 = s++;
    *v2 = 0;
  }
  return s;
}