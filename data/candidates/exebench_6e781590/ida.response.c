void __cdecl replace_char(char *buf, char from, char to)
{
  while ( *buf )
  {
    if ( *buf == from )
      *buf = to;
    ++buf;
  }
}