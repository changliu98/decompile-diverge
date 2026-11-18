const char *__cdecl copy_line(char *where, const char *what, int n)
{
  int i;

  // Copy characters up to n-1, stopping early on null, LF (\n), or CR (\r)
  for ( i = 0; i < n - 1 && *what && *what != '\n' && *what != '\r'; ++i )
  {
    *where++ = *what++;
  }

  *where = '\0';

  // Consume a trailing carriage return, if present
  if ( *what == '\r' )
    ++what;

  // Consume a trailing line feed, if present
  if ( *what == '\n' )
    ++what;

  return what;
}