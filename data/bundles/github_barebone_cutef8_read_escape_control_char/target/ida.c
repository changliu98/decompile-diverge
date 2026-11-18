char __cdecl read_escape_control_char(char c)
{
  switch ( c )
  {
    case 'n':
      return 10;
    case 't':
      return 9;
    case 'r':
      return 13;
    case 'e':
      return 27;
    case 'b':
      return 8;
    case 'f':
      return 12;
    case 'v':
      return 11;
    case 'a':
      return 7;
  }
  return c;
}