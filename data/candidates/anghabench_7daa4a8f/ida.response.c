char *__cdecl stb_skipnewline(char *s)
{
  char *sa; // [rsp+0h] [rbp-8h]

  sa = s;
  if ( *s == 13 || *s == 10 )
  {
    if ( s[1] + *s == 23 )
      sa = s + 1;
    ++sa;
  }
  return sa;
}