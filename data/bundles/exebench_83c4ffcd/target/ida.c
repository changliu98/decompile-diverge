const char *__cdecl copy_line(char *where, const char *what, int n)
{
  const char *v3; // rax
  char v4; // cl
  char *v5; // rax
  bool v7; // [rsp+1h] [rbp-25h]
  int i; // [rsp+2h] [rbp-24h]

  for ( i = 0; ; ++i )
  {
    v7 = 0;
    if ( i < n - 1 )
    {
      v7 = 0;
      if ( *what )
      {
        v7 = 0;
        if ( *what != 10 )
          v7 = *what != 13;
      }
    }
    if ( !v7 )
      break;
    v3 = what++;
    v4 = *v3;
    v5 = where++;
    *v5 = v4;
  }
  *where = 0;
  if ( *what == 13 )
    ++what;
  if ( *what == 10 )
    ++what;
  return what;
}