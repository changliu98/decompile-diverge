char __cdecl read_escape_control_char(char c)
{
  switch ( c )
  {
    case 'n':
      return '\n'; // 10 - Newline
    case 't':
      return '\t'; // 9  - Horizontal Tab
    case 'r':
      return '\r'; // 13 - Carriage Return
    case 'e':
      return '\x1b'; // 27 - Escape (non-standard C escape, kept as hex)
    case 'b':
      return '\b'; // 8  - Backspace
    case 'f':
      return '\f'; // 12 - Form Feed
    case 'v':
      return '\v'; // 11 - Vertical Tab
    case 'a':
      return '\a'; // 7  - Alert (Bell)
  }
  return c;
}